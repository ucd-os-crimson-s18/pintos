# CSCI 3453         
# Pintos Project 1: Threads
# DESIGN DOCUMENT 


## TEAM CRIMSON - https://github.com/ucd-os-crimson-s18/pintos
>> Eric Holguin

>> Jeff McMillan

>> Nikki Yesalusky


## PRELIMINARIES 
>>  https://ucd-os.slack.com/messages/C8RJM5VPA/ - general messages

>> https://ucd-os.slack.com/messages/C9A1GC1U2/ - pintos1 messages

>> https://ucd-os.slack.com/messages/C94GZD38E/ - crimson messages

## DATA STRUCTURES 
### src/threads/thread
>> struct semaphore thread_sema is a thread's semaphore

>> struct list_elem blocked_elem is a list element for blocked threads

>> fixed_point_t recent_cpu is the CPU time thread has received recently

>> fixed_point_t load_avg declares the load avg for mlfqs calculations

## ALGORITHMS
### Implementation of thread_join()
>> thread_join() does the following:

>>> Disables interrupts to prevent interleaving

>>> Removes the current thread from all_elem list

>>> Puts the thread in DYING state

>>> Turns the scheduler back on
### Implementation of alarm_clock
>> A variable that holds the ticks of timer_ticks() + ticks to sleep
### Implementation of priority donation
#### Several functions were added to calculate and adjust priority
>>> donate_priority(struct thread*, struct thread*): void

>>> reset_priority(struct thread*): void

>>> calculate_load_avg(void): void

>>> calculate_recent_cpu(void): void

>>> increment_recent_cpu(void): void

>>> calculate_priority(void): void
### Implementation of Multi-Level Feedback Queue Scheduler
>> MLFQS was handled by a combination of all of the above implementation

## SYNCHRONIZATION
>> Proper synchronization is done with the Multi-Level Feedback Queue Scheduler implementation along with priority donation.

>> The alarm clock implementation allows the scheduler to adjust priority, load average and recent CPU usage time on the ticks. Semaphores and locks were utilized to maintain critical section data integrity.

## RATIONALE
>> This design has the advantage of simplicity. The new fixed_point_t structure allows greater flexibility within the calculations of recent_cpu_time, load_avg and priority and allows encapsulation and modularization of the code to garner better usage for the next project set.

>> While there is no dynamic allocation, the child threads do have a tendency to “adjust” their own variable values during stress tests, which poses a problem during debugging.
