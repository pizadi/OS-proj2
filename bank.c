#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/types.h>
#include "mkshlock.h"
#include "stringop.h"

#define DEVICE_NAME "bank"

#define N 100

static struct file_operations fops = {
	.open = bank_open,
	.release = bank_release,
	.read = bank_read,
	.write = bank_write
}

static int major;
static int accounts[N];
static lock_t lk;

static int __init bank_init(void){
	major = register_chrdev(0, DEVICE_NAME, &fops);
	if (major < 0){
		printk(KERN_ALERT "bank_device module failed to load.\n");
		return major;
	}
	else {
		printk(KERN_ALERT "bank_device loaded on %d.\n", major);
		for (int i = 0; i < N; i++) accounts[i] = 2000000;
		lock_init(&lk, 0);
		return 0;
	}
}

static void __exit bank_exit(void){
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_ALERT "bank_device unloaded.\n");
}

static int bank_open(struct inode * inodep, struct file * filep){
	printk(KERN_INFO "bank_device opened.\n");
	return 0;
}

static int bank_release(struct inode * inodep, struct file * filep){
	printk(KERN_INFO "bank_device released.\n");
	return 0;
}

static ssize_t bank_read(struct file * filep, char * buffer, size_t len, loff_t * offset){
	char rep[2000];
	char * repp;
	lock(&lk);
	for (int i = 0; i < N; i++){
		repp = print_int(repp, rep[i]);
		if (i < N-1){
			*repp = ',';
			*(repp+1) = ' ';
			repp += 2;
		}
	}
	release(&lk);
	int errors = 0;
	errors = copy_to_user(buffer, message, strlen(message));
	return errors?(-EFAULT):((int)repp - (int)rep);
}

static ssize_t bank_write(struct file * filep, const char * buffer, size_t len, loff_t * offset){
	size_t ncopied, datalen = 50;
	char databuffer[50];
	if (len < datalen) datalen = len;
	ncopied = copy_from_user(databuffer, buffer, datalen);
	
	if (ncopied){
		printk("Couldn't copy the input from user.\n");
		return len;
	}
	else {
		char * ptr = databuffer;
		int a, b, c, d;
		ptr = put_type(ptr, &a);
		if (a > 0){
			if (a == 1){
				ptr = put_int_s(ptr, &b);
				ptr = put_int_s(ptr, &c);
				ptr = put_int_s(ptr, &d);
				if (b < 0 || b >= 100 || c < 0 || c >= 100){
					printk(KERN_ALERT "invalid account ID.\n");
					return len;
				}
				if (d < 0){
					printk(KERN_ALERT "invalid payment.\n");
					return len;
				}
				lock(&lk);
				if (accounts[b] < d){
					printk(KERN_ALERT "insufficient funds.\n");
					return len;
				}
				accounts[b] -= d;
				accounts[c] += d;
				release(&lk);
				return len;
			} else if (a == 2) {
				ptr = put_int_s(ptr, &c);
				ptr = put_int_s(ptr, &d);
				if (c >= 100 || c < 0){
					printk(KERN_ALERT "invalid account ID.\n");
					return len;
				}
				if (d < 0){
					printk(KERN_ALERT "invalid payment.\n");
					return len;
				}
				lock(&lk);
				accounts[c] += d;
				release(&lk)
				return len;
			} else if (a == 3) {
				ptr = put_int_s(ptr, &b);
				ptr = put_int_s(ptr, &d);
				if (b >= 100 || b < 0){
					printk(KERN_ALERT "invalid account ID.\n");
					return len;
				}
				if (d < 0){
					printk(KERN_ALERT "invalid payment.\n");
					return len;
				}
				lock(&lk);
				if (accounts[b] < d){
					printk(KERN_ALERT "insufficient funds.\n");
					return len;
				}
				accounts[b] -= d;
				release(&lk);
				return len;
			}
		}
		else if (a < 0){
			lock(&lk);
			for (int i = 0; i < N; i++) accounts[i] = 2000000;
			printk(KERNEL_ALERT "bank_device was reset.");
			release(&lk);
			return len;
		}
		else{
			printk(KERNEL_ALERT "invalid input given to bank_device.");
			return len;
		}
	}
}

module_init(bank_init);
module_exit(bank_exit);

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
