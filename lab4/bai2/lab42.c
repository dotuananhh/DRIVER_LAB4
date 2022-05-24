#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Do_Tuan_Anh");
MODULE_DESCRIPTION("Lab4 bai2");
MODULE_VERSION("1.1");
static struct cdev *cdev_lab4;

static int lab4_open(struct inode *inode, struct file *filp);
static int lab4_release(struct inode *inode, struct file *filp);
static ssize_t lab4_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t lab4_write(struct file *filp, const char *user_buf, size_t len, loff_t *off);

struct vchrdev
{
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;

} vchrdev;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = lab4_open,
	.release = lab4_release,
	.read = lab4_read,
	.write = lab4_write,

};

static int lab4_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int lab4_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t lab4_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	return len;
}

static ssize_t lab4_write(struct file *f, const char *user_buf, size_t len, loff_t *off)
{
	return len;
}

static int __init init_chrdev(void)
{
	int ret = 0;
	vchrdev.dev_num = MKDEV(242, 0);
	ret = register_chrdev_region(vchrdev.dev_num, 1, "lab4_2");
	if (ret < 0)
	{
		printk(KERN_INFO "Failed to register device number");
		goto failed_register_devnum;
	}
	printk(KERN_INFO "Initialize vchar driver successfully (%d, %d)", MAJOR(vchrdev.dev_num), MINOR(vchrdev.dev_num));

	vchrdev.dev_class = class_create(THIS_MODULE, "lab4_2");
	if (IS_ERR(vchrdev.dev_class))
	{
		printk(KERN_INFO "Failed create class device");
		goto failed_create_class;
	}

	vchrdev.dev = device_create(vchrdev.dev_class, NULL, vchrdev.dev_num, NULL, "lab4_2");
	if (IS_ERR(vchrdev.dev))
	{
		printk(KERN_INFO "Failed create file device");
		goto failed_create_dev;
	}
	cdev_lab4 = cdev_alloc();
	cdev_init(cdev_lab4, &fops);
	cdev_add(cdev_lab4, vchrdev.dev_num, 1);

	printk(KERN_INFO "Successfully");
	return 0;

failed_create_dev:
	class_destroy(vchrdev.dev_class);
failed_create_class:
	unregister_chrdev_region(vchrdev.dev_num, 1);
failed_register_devnum:
	return ret;
}

static void __exit exit_chrdev(void)
{
	cdev_del(cdev_lab4);

	device_destroy(vchrdev.dev_class, vchrdev.dev_num);

	class_destroy(vchrdev.dev_class);

	unregister_chrdev_region(vchrdev.dev_num, 1);

	printk(KERN_INFO "Remove and Exit successfully\n");
}

module_init(init_chrdev);
module_exit(exit_chrdev);
