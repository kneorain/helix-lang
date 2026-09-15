class Buf { var n: i32; }
fn sink(@move b: Buf) { }
fn read(b: Buf) { }
fn main() {
    var a = Buf{ n: 1 };
    sink(a);
    read(a);                                // expect: error 'a' is used after being moved; note moved here (line 6)

    var b = Buf{ n: 2 };
    sink(b);
    b = Buf{ n: 3 };
    read(b);                                // expect: clean -- reassigned

    var c = Buf{ n: 4 };
    if c.n > 0 { sink(c); }
    read(c);                                // expect: error -- moved on one branch, used after the join

    var d = Buf{ n: 5 };
    if d.n > 0 { sink(d); return; }
    read(d);                                // expect: clean -- the moving path returned

    var e = Buf{ n: 6 };
    while e.n > 0 {
        read(e);                            // expect: error -- moved on the previous iteration
        sink(e);
    }
}

// --- lit wiring -----------------------------------------------------------
// MoveCheck's flow facts: reassignment revives, a join is moved if any
// predecessor moved, a returning branch contributes nothing, a loop back-edge
// carries the move into the next iteration.
//
// RUN: { %kairo %s --type-check-only 2>&1 || true; } | %FileCheck %s --check-prefix=DIAG
//
// DIAG:      use_after_move.k:7:{{[0-9]+}}: error [{{[A-Z0-9]+}}]: {{.*}}'a' is used after being moved
// DIAG-NEXT: use_after_move.k:6:{{[0-9]+}}: note
// DIAG-NOT:  use_after_move.k:12:{{[0-9]+}}: error
// DIAG:      use_after_move.k:16:{{[0-9]+}}: error [{{[A-Z0-9]+}}]: {{.*}}'c'
// DIAG-NOT:  use_after_move.k:20:{{[0-9]+}}: error
// DIAG:      use_after_move.k:24:{{[0-9]+}}: error [{{[A-Z0-9]+}}]: {{.*}}'e'
