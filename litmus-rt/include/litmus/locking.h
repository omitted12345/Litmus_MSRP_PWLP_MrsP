#ifndef LITMUS_LOCKING_H
#define LITMUS_LOCKING_H

struct litmus_lock_ops;

/* Generic base struct for LITMUS^RT userspace semaphores.
 * This structure should be embedded in protocol-specific semaphores.
 */
struct litmus_lock {
	struct litmus_lock_ops *ops;
	int type;
};

struct litmus_lock_ops {
	/* Current task tries to obtain / drop a reference to a lock.
	 * Optional methods, allowed by default. */
	int (*open)(struct litmus_lock*, void* __user);
	int (*close)(struct litmus_lock*);

	/* Current tries to lock/unlock this lock (mandatory methods). */
	int (*lock)(struct litmus_lock*);
	int (*unlock)(struct litmus_lock*);

	/* The lock is no longer being referenced (mandatory method). */
	void (*deallocate)(struct litmus_lock*);
};

struct mrsp_semaphore {
	int id;
	int order; // the lock order for nested access

	struct litmus_lock litmus_lock;
	spinlock_t lock;

	/* tasks queue for resource access */
	struct task_list *tasks_queue;

	/* priority ceiling per cpu */
	int *prio_per_cpu;

	int *usr_info;

	/*FIFO tickets*/
	atomic_t owner_ticket;
	atomic_t next_ticket;
};

struct msrp_semaphore {
	int id;
	int order; // the lock order for nested access

	struct litmus_lock litmus_lock;
	spinlock_t lock;

	int *usr_info;

	/*FIFO tickets*/
	atomic_t owner_ticket;
	atomic_t next_ticket;
};

struct fifop_semaphore {
	int id;
	int order; // the lock order for nested access

	struct litmus_lock litmus_lock;
	spinlock_t lock;

	/* tasks queue for resource access */
	struct task_list *tasks_queue;

	int *usr_info;

	/*FIFO tickets*/
	atomic_t owner_ticket;
	atomic_t next_ticket;
};

#endif


