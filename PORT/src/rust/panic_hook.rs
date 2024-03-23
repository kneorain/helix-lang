use crate::python::shared::unknown_int::NumericType;
use backtrace::{ Backtrace, BacktraceFrame };
use std::fs::read_to_string;
use std::io;
use std::sync::atomic::AtomicBool;
use std::{ panic, thread };
use std::time;
use std::cell::RefCell;
use std::thread_local;
use crate::__panic__;

#[macro_export]
macro_rules! panic_any {
    ($arg:expr) => {
        // extract the typeof and the messge, if the typeof is str then only the message is passed
        let r#typeof = std::any::type_name_of_val(&$arg);
        panic!("{typeof}\r\0\r\0\r\r\0{}",$arg)
    };
}

pub fn better_panic(panic_info: &panic::PanicInfo) {
    error!("panic called");
    static mut PANIC_LOCK: AtomicBool = AtomicBool::new(false);
    info!("panic lock acquired");

    thread_local! {
        static START: RefCell<time::Instant> = RefCell::new(time::Instant::now());
    }

    // This is safe as it is called here and only in this function.
    #[allow(redundant_semicolons)]
    START.with(|start| {;//"""REMOVE-STACK"""//

        let start = start.borrow_mut();
        while unsafe { PANIC_LOCK.load(std::sync::atomic::Ordering::SeqCst) } {
            std::thread::sleep(time::Duration::from_millis(10));
            warn!("waiting for panic to be released");
            info!("time elapsed: {}ms", start.elapsed().as_millis());
        }
        
        warn!("panic lock acquired");
        unsafe {
            PANIC_LOCK.store(true, std::sync::atomic::Ordering::SeqCst);
        }
        info!("took {}ms to acquire lock @ thread~{}", start.elapsed().as_millis(), thread::current().name().unwrap_or("no-name"));

        let backtrace = Backtrace::new();//"""REMOVE-STACK"""//
        let current_thread = thread::current();
        let thread_name = current_thread.name().unwrap_or("unknown");

        let frames = backtrace.frames();
        let relevant_frames = filter_relevant_frames(frames);

        for (index, frame) in relevant_frames.iter().enumerate() {
            let symbol = match frame.symbols().get(0) {
                Some(s) => s,
                None => {
                    continue;
                }
            };

            let filename = match symbol.filename() {
                Some(s) => s,
                None => {
                    continue;
                }
            };

            let filename = match filename.to_str() {
                Some(s) => s,
                None => {
                    continue;
                }
            };

            let line_no = match symbol.lineno() {
                Some(s) => s,
                None => {
                    continue;
                }
            };

            let pos = match index {
                0 => 0,
                _ if index < relevant_frames.len() - 1 => 1,
                _ => 2,
            };

            let panic_payload = format!("{}", panic_info)
                .split("\n")
                .map(|s| s.to_owned())
                .collect::<Vec<String>>()[1..]
                .join("\n");

            __panic__!(
                panic_payload,
                None,
                file = filename,
                line_no = NumericType::Uint(line_no),
                multi_frame = if relevant_frames.len() > 1 { true } else { false },
                pos = pos as i8,
                thread_name = if thread_name != "main" { thread_name } else { "" },
                lang = "rs"
            );

            current_thread.unpark();
        }

        unsafe {
            PANIC_LOCK.store(false, std::sync::atomic::Ordering::SeqCst)
        }
        
        info!("panic lock released");
    });
}

fn read_lines(filename: &str) -> Result<Vec<String>, io::Error> {
    Ok(read_to_string(filename)?.lines().map(String::from).collect())
}

fn filter_relevant_frames(frames: &[BacktraceFrame]) -> Vec<&BacktraceFrame> {
    let mut relevant_frames: Vec<&BacktraceFrame> = Vec::new();

    for frame in frames {
        let symbol = match frame.symbols().get(0) {
            Some(s) => s,
            None => {
                continue;
            }
        };

        let filename = match symbol.filename() {
            Some(s) =>
                match s.to_str() {
                    Some(s) => s,
                    None => {
                        continue;
                    }
                }
            None => {
                continue;
            }
        };

        let line_no = match symbol.lineno() {
            Some(s) => s,
            None => {
                continue;
            }
        };

        let lines = &(match read_lines(filename) {
            Ok(val) => val,
            Err(_) => {
                continue;
            }
        });

        if lines.len() < ((line_no - 1) as usize) {
            continue;
        }

        let line = lines.get((line_no - 1) as usize).unwrap();

        if
            !filename.contains("rustc") &&
            !filename.contains("backtrace") &&
            !filename.contains("vctools") &&
            !line.contains(r#";//"""REMOVE-STACK"""//"#)
        {
            relevant_frames.push(frame);
        }
    }

    relevant_frames.reverse();

    return relevant_frames;
}
