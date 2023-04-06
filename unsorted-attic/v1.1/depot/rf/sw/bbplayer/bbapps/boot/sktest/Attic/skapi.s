d7 1
d17 10
a26 29
.text
.align 2
.globl sk_entry1
.type symbol,@function
.ent sk_entry1
sk_entry1:
	li	v0, 0
	SK_ENTRY_AND_RETURN
.end sk_entry1

.text
.align 2
.globl sk_entry2
.type symbol,@function
.ent sk_entry2
sk_entry2:
	li	v0, 1
	SK_ENTRY_AND_RETURN
.end sk_entry2

.text
.align 2
.globl sk_entry3
.type symbol,@function
.ent sk_entry3
sk_entry3:	
	li	v0, 2
	SK_ENTRY_AND_RETURN
.end sk_entry3
d28 3
