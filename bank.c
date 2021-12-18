#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#include "mkshlock.h"

#define DEVICE_NAME "bank_device"
MODULE_LICENSE("GPL");

#define N 100

static struct file_operations fops = {
	.open = bank_open,
	.release = bank_release,
	.read = bank_read,
	.write = bank_write
}

static int major;
static int accounts[N];

static int __init bank_init(void){
	major = register_chrdev(0, DEVICE_NAME, &fops);
	if (major < 0){
		printk(KERN_ALERT "bank_device module failed to load.\n");
		return major;
	}
	else {
		printk(KERN_ALERT "bank_device loaded on %d.\n", major);
		for (int i = 0; i < N; i++) accounts[i] = 2000000; 
		return 0;
	}
}

static void __exit bank_exit(void){
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_ALERT "bank_device unloaded.\n");
}

static ssize_t bank_read(struct file * filep, char * buffer, size_t len, loff_t * offset){
	char rep[2000];

}

static ssize_t bank_write(struct file * filep, const char *, size_t len, loff_t * offset){

}
