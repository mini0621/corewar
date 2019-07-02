.name"test"
.comment"test all valid operations combinations"

live %5
live %:test

ld %1, r1
ld 1, r1

st r1, r1
st r1, 1

add r1, r1, r1

sub r1, r1, r1

and r1, r1, r1
and r1, %1, r1
and r1, %:test, r1
and r1, 1, r1
and r1, :test, r1
and %1, r1, r1
and %:test, r1, r1
and %1, %1, r1
and %:test, %:test, r1
and %1, 1, r1
and %:test, :test, r1
and 1, r1, r1
and :test, r1, r1
and 1, %1, r1
and :test, %:test, r1
and 1, 1, r1
and :test, :test, r1

or r1, r1, r1
or r1, %1, r1
or r1, %:test, r1
or r1, 1, r1
or r1, :test, r1
or %1, r1, r1
or %:test, r1, r1
or %1, %1, r1
or %:test, %:test, r1
or %1, 1, r1
or %:test, :test, r1
or 1, r1, r1
or :test, r1, r1
or 1, %1, r1
or :test, %:test, r1
or 1, 1, r1
or :test, %:test, r1

xor r1, r1, r1
xor r1, %1, r1
xor r1, %:test, r1
xor r1, 1, r1
xor r1, :test, r1
xor %1, r1, r1
xor %1, %1, r1
xor %:test, %:test, r1
xor %1, 1, r1
xor %:test, :test, r1
xor 1, r1, r1
xor 1, %1, r1
xor 1, 1, r1

zjmp %1
zjmp %:test

ldi r1, r1, r1
ldi r1, %1, r1
ldi r1, %:test, r1
ldi %1, r1, r1
ldi %1, %1, r1
ldi 1, r1, r1
ldi :test, r1, r1
ldi 1, %1, r1

sti r1, r1, r1
sti r1, r1, %1
sti r1, %1, r1
sti r1, %1, %1
sti r1, %:test, %:test
sti r1, 1, r1
sti r1, 1, %1
sti r1, :test, %:test

fork %1
fork %:test

lld %1, r1
lld %:test, r1
lld 1, r1
lld :test, r1

lldi r1, r1, r1
lldi r1, %1, r1
lldi r1, %:test, r1
lldi %1, r1, r1
lldi %:test, r1, r1
lldi %1, %1, r1
lldi %1, %:test, r1
lldi 1, r1, r1
lldi :test, r1, r1
lldi 1, %1, r1
lldi :test, %:test, r1

lfork %1
lfork %:test

aff r1

test:
