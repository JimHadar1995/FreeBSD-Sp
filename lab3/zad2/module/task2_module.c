#include <sys/param.h>
#include <sys/queue.h>
#include <sys/sdt.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysproto.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/kdb.h>
#include <sys/dtrace_bsd.h>

struct data {
	char *str;
};

static int
isVowel(char ch) {
	return (ch =='A' || ch == 'E' || ch =='I' || ch =='O' || ch == 'U' ||
		ch =='a' || ch == 'e' || ch =='i' || ch =='o' || ch == 'u');
}

static int calculate_vowel(struct thread *td, void *arg) {
	struct data *d = (struct data*) arg;
	char *str = d->str;
	int length = strlen(str);
	int error = 0;
	for (int i = 0; i < length; i++) {
		if (isVowel(str[i])) {
			error++;
		}
	}
	uprintf("Count of vowels in %s is %d\n", d->str, error);
	return (error);
}

/*
 * The `sysent' for the new syscall
 */
static struct sysent vowel_sysent = {
	1, // sy_narg
	calculate_vowel // sy_call
};
/*
 * The offset in sysent where the syscall is allocated.
 */

static int offset = NO_SYSCALL;
/*
 * The function called at load/unload.
 */
static int event_handler(struct module *module, int event, void *arg) {
	int error = 0;
	switch (event) {
		case MOD_LOAD:
			uprintf("syscall VOWEL loaded\n");
		break;
		case MOD_UNLOAD:
			uprintf("syscall VOWEL unloaded\n");
		break;
		default:
			error = EOPNOTSUPP;
		break;
	}
	return (error);
}
SYSCALL_MODULE(vowel, &offset, &vowel_sysent, event_handler, NULL);
