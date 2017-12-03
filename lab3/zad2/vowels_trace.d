fbt::calculate_vowel:entry
{
	printf("\n---Start calculate---\n");
	str = copyinstr(*(uintptr_t *) arg1);
}
syscall::openat*:entry
{
	all++;
}
syscall::openat*:return
/arg1 >= 0 /
{
	success++;
}
fbt::calculate_vowel:return
/ arg1 % 2 == 0 /
{
	even++;
}
fbt::calculate_vowel:return
/ arg1 % 2 == 1 /
{
	odd++;
}
fbt::calculate_vowel:return
/ strlen(str) == 0 /
{
	empty++;
}
fbt::calculate_vowel:return
{
	printf("\n---End calculate---\n");
}
tick-5s
{
	printf("%4i %3i %5i %7i %3i", even, odd, empty, success, all);
}
BEGIN
{
	printf("%s | %s | %s | %s | %s\n", "even", "odd", "empty", "success", "all");
}
