use std::path::{Path, PathBuf};
use std::sync::atomic::AtomicBool;

use cxx::UniquePtr;

use crate::cpp::FileReader::{self, T_FileReader};

pub struct File<'cxx> {
    file_reader: UniquePtr<T_FileReader<'cxx>>,
    file_path: PathBuf, // not sure if this is valid in cpp
    file_content: &'cxx str,
    locked: AtomicBool,
    references: usize,
}

impl<'a, 'cxx> File<'cxx> {
    pub fn new(file_path: PathBuf) -> Self {
        let mut file_reader = FileReader::init(file_path.display().to_string().as_str());
        Self {
            file_content: file_reader.read_file(),
            file_reader,
            file_path: file_path,
            locked: AtomicBool::new(false),
            references: 0,
        }
    }

    pub fn get_file_path(&'a self) -> &'a Path {
        &self.file_path.as_path()
    }

    pub fn get_file_content(&'a self) -> &'cxx str {
        self.file_content
    }

    pub fn file_size(&self) -> usize {
        self.file_content.len()
    }
    /// Waits for the file_reader to be unlocked.
    pub fn file_reader(&self) -> &UniquePtr<T_FileReader<'cxx>> {
        &self.file_reader
    }
    // TODO: FIX
    // /// Call the function again to unlock the file_reader.
    // pub fn lock(&'a self) -> Box<dyn Fn()> {
    //     self.locked.store(true, std::sync::atomic::Ordering::SeqCst);
    //     Box::new(|| {
    //         self.locked
    //             .store(false, std::sync::atomic::Ordering::SeqCst);
    //     })
    // }
    #[inline(always)]
    pub fn is_locked(&self) -> bool {
        self.locked.load(std::sync::atomic::Ordering::SeqCst)
    }
}
