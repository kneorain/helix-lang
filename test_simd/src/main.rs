use std::arch::x86_64::*;
use std::hint::black_box;
use std::time::{Duration, Instant};

#[unroll::unroll_for_loops] // this unroll all for loops in the function ...
const fn create_punctuation_lookup_table() -> [bool; 256] {
    let mut table = [false; 256];
    for byte in 0u8..=255u8 {
        table[byte] = matches!(byte as u8, b'!'..=b'/' | b':'..=b'@' | b'['..=b'`' | b'{'..=b'~');
    }
    table
}

const PUNCTUATION_LOOKUP_TABLE: [bool; 256] = create_punctuation_lookup_table();

fn main() {
    const ITERATIONS: u32 = 100000000;

    let expanded_ranges: [u8; 32] = [
        // Range: ! to /
        b'!', b'"', b'#', b'$', b'%', b'&', b'\'', b'(', b')', b'*', b'+', b',', b'-', b'.', b'/',
        // Range: : to @
        b':', b';', b'<', b'=', b'>', b'?', b'@', // Range: [ to `
        b'[', b'\\', b']', b'^', b'_', b'`', // Range: { to ~
        b'{', b'|', b'}', b'~',
    ];

    use rand::Rng;

    let mut simd: u128 = 0;
    let mut match_: u128 = 0;
    let mut ptr_lookup: u128 = 0;
    let mut idx_lookup: u128 = 0;

    let mut correct_simd = 0;
    let mut correct_match = 0;
    let mut correct_ptr_lookups = 0;
    let mut correct_idx_lookups = 0;
    unsafe {
        let punc = _mm256_loadu_si256(std::mem::transmute::<*const u8, *const __m256i>(
            expanded_ranges.as_ptr(),
        ));

        for _ in 0..ITERATIONS {
            let byte: u8 = black_box(rand::thread_rng().gen_range(0..=255));

            let simd_start = Instant::now();
            let byte_vec = _mm256_set1_epi8(byte as i8);

            let result = _mm256_cmpeq_epi8(byte_vec, punc);

            let test = _mm256_movemask_epi8(result) != 0;

            let elapsed = simd_start.elapsed();

            if test {
                correct_simd += 1;
            }

            simd += elapsed.as_nanos();

            let match_start = Instant::now();
            let test =
                matches!(black_box(byte), b'!'..=b'/' | b':'..=b'@' | b'['..=b'`' | b'{'..=b'~');
            let elapsed = match_start.elapsed();
            if test {
                correct_match += 1;
            }

            match_ += elapsed.as_nanos();

            let lookup_start = Instant::now();
            let test = PUNCTUATION_LOOKUP_TABLE
                .as_ptr()
                .add(black_box(byte) as usize)
                .read();

            let elapsed = lookup_start.elapsed();
            if test {
                correct_ptr_lookups += 1;
            }
            ptr_lookup += elapsed.as_nanos();

            let idx_lookup_start = Instant::now();
            let test = PUNCTUATION_LOOKUP_TABLE[black_box(byte) as usize];
            let elapsed = idx_lookup_start.elapsed();
            if test {
                correct_idx_lookups += 1;
            }
            idx_lookup += elapsed.as_nanos();
        }
    }

    let average_simd = simd / ITERATIONS as u128;
    let average_match = match_ / ITERATIONS as u128;
    let average_lookup = ptr_lookup / ITERATIONS as u128;
    let average_idx_lookup = idx_lookup / ITERATIONS as u128;

    println!("Average SIMD Duration: {:?}", average_simd);
    println!("Average Match Duration: {:?}", average_match);
    println!("Average Lookup Duration: {:?}", average_lookup);
    println!("Average Idx Lookup Duration: {:?}", average_idx_lookup);

    println!("Correct SIMD: {}", correct_simd);
    println!("Correct Match: {}", correct_match);
    println!("Correct Ptr Lookup: {}", correct_ptr_lookups);
    println!("Correct Idx Lookup: {}", correct_idx_lookups);
}
