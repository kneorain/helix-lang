
#[derive(Debug, Clone)]
enum COLORS {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
}

const COLORS: [COLORS; 12] = [
    COLORS::RED,
    COLORS::GREEN,
    COLORS::YELLOW,
    COLORS::MAGENTA,
    COLORS::BLUE,
    COLORS::CYAN,
    COLORS::BrightRed,
    COLORS::BrightGreen,
    COLORS::BrightYellow,
    COLORS::BrightBlue,
    COLORS::BrightMagenta,
    COLORS::BrightCyan,
];

pub struct DebugCounter {
    color_count: AtomicU8,
    char_count: AtomicUsize,
}

impl DebugCounter {
    /// println! style usage,
    /// so a message and format args
   pub fn new() -> Self {
        return DebugCounter {
            color_count: AtomicU8::new(0),
            char_count: AtomicUsize::new(0),
        };
    }

    const CHARS: [char; 62] = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    ];

    pub fn print(&mut self, line_number: u32) {
        self.char_count.fetch_add(1, Ordering::SeqCst);
        print!(
            "\u{001b}[{}m({}|{})\u{001b}[0m|",
            self.color(),
            self.char(),
            line_number
        );
    }

    fn color(&mut self) -> u8 {
        let color_count = self.color_count.load(Ordering::SeqCst);
        self.color_count
            .store((color_count + 1) % (COLORS.len() as u8), Ordering::SeqCst);
        return COLORS[color_count as usize].clone() as u8;
    }

    fn char(&mut self) -> char {
        let char = self.char_count.load(Ordering::SeqCst);
        self.char_count
            .store((char + 1) % (Self::CHARS.len() as usize), Ordering::SeqCst);
        return Self::CHARS[char as usize];
    }

    pub fn reset(&mut self) {
        self.color_count.store(0, Ordering::SeqCst);
        self.char_count.store(0, Ordering::SeqCst);
    }

    pub fn print_char(&mut self, c: &str) {
        self.char_count.fetch_add(1, Ordering::SeqCst);
        print!("\u{001b}[{}m{}\u{001b}[0m", self.color(), c);
    }
}

use std::sync::{atomic::{AtomicU8, AtomicUsize, Ordering}, OnceLock};

pub use crate::dbg_trace;
pub static mut DBG: OnceLock<DebugCounter> = OnceLock::new();
#[macro_export]
macro_rules! dbg_trace {
    () => {
        #[cfg(feature = "debug-trace")]
        unsafe {crate::rust::debug_counter::DBG.get_mut().unwrap().print(line!());}
    };
    ($literal:literal) => {
        #[cfg(feature = "debug-trace")]
        unsafe {crate::rust::debug_counter::DBG.get_mut().unwrap().print_char($literal.into());}
    };
    ($($arg:tt)*) => { // dbg_trace(reset, "hello we start trace {}", "hello we start trace {})

    #[cfg(feature = "debug-trace")]
    unsafe{
            println!();
            print!($($arg)*);
            crate::rust::debug_counter::DBG.get_or_init(|| crate::rust::debug_counter::DebugCounter::new());
            crate::rust::debug_counter::DBG.get_mut().unwrap().reset()
        }
    };

}