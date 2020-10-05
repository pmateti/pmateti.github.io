/*
  Nov 2018, Jun 2015 pmateti@wright.edu

  This is an example LKM used in describing a SysCall Lab in
  http://cecs.wright.edu/~pmateti/Courses/4420/
   
  This Linux kernel module can redirect one system call to another,
  perhaps to sys-ni-syscall (sys-call-not-implemented).  Thx to many
  blogs.  Essential info is from kernel source tree
  Documentation/../kbuild */

#include <linux/module.h>
#include <linux/unistd.h>	/* __NR_ entries */

MODULE_AUTHOR("pmateti@wright.edu");
MODULE_DESCRIPTION("syscall redirect 20181112");
MODULE_LICENSE("GPL");

/* Read lecture notes 4420/Lectures/Hardening/SysCalls/ for an
   explanation of how the following values are obtained. */

#define __NR_ni 7                       /* NR of sys_ni_syscall */
#define __NR_MAX 334                    /* NR max; TBD check */
#define SYSCALLTBL319020 0xffffffff81801680 /* 3.19.0-20-lowlatency  */
#define SYSCALLTBL401000 0xffffffff81801400 /* 4.0.1 */
#define SYSCALLTBL418010 0xffffffff81e001c0 /* 4.18.0-10-generic */
#define SYSCALLTBL418011 0xffffffff844001c0 /* 4.18.0-11-generic */
#define SYSCALLTBL SYSCALLTBL418011

static void * * sys_call_table = (void *) SYSCALLTBL; /* decl better! */
pte_t * sys_call_table_pte = 0; /* for now */

/* Stores a ptr to a function.  Study its declaration.  Unused in this
   LKM; it is here just as an example.  Delete later. Useful when
   implementing unfreeze.  TBD use varargs. */

static long (*osyscallp)(long x, long y) = 0;

/* pre:: (i) sys_call_table is set; (ii) calling process must be
   root-owned, (iii) nrdel, nradd are valid sys call numbers;; post::
   (i) the entry for nrdel is replaced with nradd; (ii) return the
   old-sys_call_table[nrdel] address;; Q: Should this be atomic? A:
   Not sure.  Keep the duration for which the sys-call-table page is
   RW as short as possible. */

static void * syscallredirect(int nrdel, int nradd) {
  uid_t owner = 0;              /* set it to geteuid() */
  if (owner != 0)    {
    printk(KERN_DEBUG "LKM sysredirect owner %d is not root\n", owner);
    /* Use printk sparingly. */
    return 0;                   /* failed syscall */
  }
  if (0 > nrdel || nrdel > __NR_MAX ) {
    printk(KERN_DEBUG "LKM sysredirect nrdel %d invalid\n", nrdel);
    return 0;
  }
  if (0 > nradd || nradd > __NR_MAX ) {
    printk(KERN_DEBUG "LKM sysredirect nradd %d invalid\n", nradd);
    return 0;
  }
  {
    void * oldptr = osyscallp = sys_call_table[nrdel];
    sys_call_table_pte->pte |= _PAGE_RW;       /* set page to RW */
    sys_call_table[nrdel] = sys_call_table[nradd];
    sys_call_table_pte->pte &= ~ _PAGE_RW;	/* set page back to RO */
    printk(KERN_DEBUG "LKM sysredirect[nrdel %d := nradd %d] == %p\n",
           nrdel, nradd, sys_call_table[nradd]); /* expensive! should delete */
    return oldptr;
  }
}

static int __init myinit(void) {
  unsigned int unused = 0;
  pte_t * sys_call_table_pte = lookup_address((long) sys_call_table, & unused);
  void  * sys_ni_syscall = sys_call_table[__NR_ni];
  sys_call_table_pte->pte |= _PAGE_RW;       /* set page to RW */
  sys_call_table[__NR_ni] = syscallredirect; /* just checking */
  /* for you TODO: really, where to plant *this* syscall? */
  sys_call_table[__NR_ni] = sys_ni_syscall; /* put it back */
  sys_call_table_pte->pte &= ~ _PAGE_RW; /* set page back to RO */
  printk(KERN_DEBUG "LKM sysredirect init "
         "sys_call_table %p, sys_ni_syscall %p\n",
         sys_call_table, sys_ni_syscall);
  return 0;
}

static void __exit myexit(void) {
  printk(KERN_DEBUG "LKM sysredirect exits\n");
}  

module_init(myinit);
module_exit(myexit);

/* -eof- */
