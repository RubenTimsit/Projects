#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>


asmlinkage long sys_hello(void) {
	 printk("Hello, World!\n");
	 return 0;
}

asmlinkage long sys_set_weight(int weight)
{
    if(weight<0)
        return -EINVAL;
    current->process_weight=weight;
    return 0;
}
asmlinkage long sys_get_weight(void)
{
    return current->process_weight;
}

asmlinkage long sys_get_siblings_sum(void) {
    struct task_struct *parent_process = current->real_parent;
    struct task_struct *child;
    int weight_sum = 0;
    if(list_is_singular(&parent_process->children))
        return -ESRCH;
    list_for_each_entry(child, &parent_process->children, sibling) {
        if(child != current)
            weight_sum += child->process_weight;
    }
    return weight_sum;

}

asmlinkage pid_t sys_get_lightest_divisor_ancestor(void) {
    struct task_struct *current_process = current;
    int curr_weight = current_process->process_weight;
    int lightest_divisor_weight = current_process->process_weight;
    pid_t lightest_divisor_ancestor = current_process->pid;
    while(current_process->real_parent != current_process) {
        current_process = current_process->real_parent;
        if(current_process->process_weight != 0 &&
        curr_weight % current_process->process_weight == 0 &&
        current_process->process_weight < lightest_divisor_weight) {
            lightest_divisor_weight = current_process->process_weight;
            lightest_divisor_ancestor = current_process->pid;
        }
    }
    return lightest_divisor_ancestor;
}