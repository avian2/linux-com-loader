MEMORY
{
	RAM (rwx) : ORIGIN = 0x100, LENGTH = 64K
}

SECTIONS
{
	.text :
	{
		*(.text)
	} >RAM

	.data :
	{
		*(.data)
	} >RAM
}
