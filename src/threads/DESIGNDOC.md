# CSCI 3453         
# Pintos Project 1: Threads
# DESIGN DOCUMENT 

##---- GROUP ----
Eric Holguin <ERIC.HOLGUIN@UCDENVER.EDU>
Nikki, Yesalusky <NIKKI.YESALUSKY@UCDENVER.EDU>
Jeff McMillan <JEFF.MCMILLAN@UCDENVER.EDU>

## PRELIMINARIES 
>> If you have any preliminary comments on your submission, notes for
>> the TAs, or extra credit, please give them here.

>> Please cite any offline or online sources you consulted while
>> preparing your submission, other than the Pintos documentation,
>> course text, and lecture notes.



## DATA STRUCTURES 
>> Copy here the declaration of each new or changed ‘struct’ or ‘struct’
>> member, global or static variable, ‘typedef’, or enumeration.
>> Identify the purpose of each in 25 words or less.

#####Added to struct thread:

struct semaphore thread_sema;  /* Thread's semaphore*/
struct list_elem blocked_elem; /* List element for blocked threads */
int nice;                      /*How nice the thread should be to others. */
int64_t alarm_clock;           /* Time for thread to wake up */
fixed_point_t recent_cpu;      /*CPU time thread has received recently */


A "latch" is a new synchronization primitive. Acquires block
until the first release. Afterward, all ongoing and future
acquires pass immediately.
/* Latch. */
struct latch
{
bool released; /* Released yet? */
struct lock monitor_lock; /* Monitor lock. */
struct condition rel_cond; /* Signaled when released. */
};


Added to struct thread:
/* Members for implementing thread_join(). */
struct latch ready_to_die; /* Release when thread about to die. */
struct semaphore can_die; /* Up when thread allowed to die. */
struct list children; /* List of child threads. */
list_elem children_elem; /* Element of ‘children’ list. */


##---- ALGORITHMS ----
>> Briefly describe your implementation of thread_join() and how it
>> interacts with thread termination.
thread_join() finds the joined child on the thread’s list of
children and waits for the child to exit by acquiring the child’s
Appendix D: Project Documentation 101
ready_to_die latch. When thread_exit() is called, the thread
releases its ready_to_die latch, allowing the parent to continue.


##---- SYNCHRONIZATION ----
>> Consider parent thread P with child thread C. How do you ensure
>> proper synchronization and avoid race conditions when P calls wait(C)
>> before C exits? After C exits? How do you ensure that all resources
>> are freed in each case? How about when P terminates without waiting,
>> before C exits? After C exits? Are there any special cases?
C waits in thread_exit() for P to die before it finishes its own
exit, using the can_die semaphore "down"ed by C and "up"ed by P as
it exits. Regardless of whether whether C has terminated, there
is no race on wait(C), because C waits for P’s permission before
it frees itself.
Regardless of whether P waits for C, P still "up"s C’s can_die
semaphore when P dies, so C will always be freed. (However,
freeing C’s resources is delayed until P’s death.)
The initial thread is a special case because it has no parent to
wait for it or to "up" its can_die semaphore. Therefore, its
can_die semaphore is initialized to 1.


##---- RATIONALE ----
>> Critique your design, pointing out advantages and disadvantages in
>> your design choices.
This design has the advantage of simplicity. Encapsulating most
of the synchronization logic into a new "latch" structure
abstracts what little complexity there is into a separate layer,
making the design easier to reason about. Also, all the new data
members are in ‘struct thread’, with no need for any extra dynamic
allocation, etc., that would require extra management code.
On the other hand, this design is wasteful in that a child thread
cannot free itself before its parent has terminated. A parent
thread that creates a large number of short-lived child threads
could unnecessarily exhaust kernel memory. This is probably
acceptable for implementing kernel threads, but it may be a bad
idea for use with user processes because of the larger number of
resources that user processes tend to own.
