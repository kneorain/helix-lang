fn a(x: fn(i32) -> void) { }
fn b(x: fn(@inout i32) -> void) { }
fn c(x: fn(@move i32) -> void) { }
fn d(x: fn(@inout i32) -> void) { }
// expect: no diagnostics; a.x, b.x, c.x are three distinct canonicals;
// expect: b.x and d.x are the same canonical (dump: identical canonical pointer / same rendered type)

// --- lit wiring -----------------------------------------------------------
// Modes are in the fn-pointer canonical's key (CanonicalTypeStore::func).
//
// TODO: the canonical-identity half (a/b/c distinct, b == d) needs a SEMA
// golden block from `--print-sema` on a built compiler; the dump's rendering
// of a moded fn-pointer type is not settled yet, so none is written here.
//
// RUN: { %kairo %s --type-check-only 2>&1 || true; } | %FileCheck %s --check-prefix=DIAG --allow-empty
//
// DIAG-NOT: {{error|warning}} [
