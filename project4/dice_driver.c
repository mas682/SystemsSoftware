/*
 *
 *
 * Valerie Henson <val@nmt.edu>
 *Matt Stropkey
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

/*
 * dice_driver_read is the function called when a process calls read() on
 * /dev/dice.  It writes dice rolls  to the buffer passed in the
 * read() call.
*/ 
unsigned char get_random_byte(int max){
	unsigned char c;
	get_random_bytes(&c, 1);
	return c%max+1;
}

static ssize_t dice_driver_read(struct file * file, char * buf, 
			  size_t count,loff_t *ppos)
{
	if(count < 1)			//cannot roll a negative amount of dice
		return -EINVAL;

	int rolls =0;		//the number of dice rolled so far
	int len = 0;		//number of bytes written to buffer
	int pos = 0;		//current position in dice array
	
	char dice[count];
	char temp = 0;
	do{
		temp = (char)get_random_byte(6);	//get a die value
		dice[pos] = temp;			//set the value in the dice array
		rolls++;				//increment the number of rolls that have occurred
		pos++;					//increment the position in the dice array
		len++;					//used to return how many bytes returned
	}while(rolls < count);
	if (copy_to_user(buf, dice, count))	//copy the dice to the buffer
		return -EINVAL;
	return len;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations dice_driver_fops = {
	.owner		= THIS_MODULE,
	.read		= dice_driver_read,
};

static struct miscdevice dice_driver_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"dice_driver",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_driver_fops
};

static int __init
dice_driver_init(void)
{
	int ret;

	/*
	 * Create the "dice" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/dice device using
	 * the default rules.
	 */
	ret = misc_register(&dice_driver_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register dice driver misc device\n");

	return ret;
}

module_init(dice_driver_init);

static void __exit
dice_driver_exit(void)
{
	misc_deregister(&dice_driver_dev);
}

module_exit(dice_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matt Stropkey");
MODULE_DESCRIPTION("\"dice_driver\" minimal module");
MODULE_VERSION("dev");
