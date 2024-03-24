pub mod token;
pub mod config;
pub mod panic_hook;
use panic_hook::better_panic;

// TODO: Make this into a proc-macro.
pub trait Label {
    fn label() -> &'static str;
}

pub fn init_rust() {
    info!("initializing rust bootstrap");
    warn!("hooking rust panic handler to python panic handler");
    std::panic::set_hook(Box::new(better_panic)); //"""REMOVE-STACK"""//
    trace!("hooked rust panic handler to python panic handler");
    // ................................ //
    info!("rust bootstrap initialized");
}
