use PracticalExam
go

/*
Dirty read is a concurrency problem which occurs on the 
read uncommitted isolation level.

A dirty read means that a transaction reads uncommitted data.
This means that this transaction will read the value written
by the other transaction before it rollbacks, thus reading wrong
data. This happens because under read uncommitted
there are no shared locks acquired meaning that the exclusive
lock acquired by the update does not stop the reading.

The solution is to run the first tran under read committed
isolation level (or higher)
so that shared locks are acquired when trying to read.
This means that the exclusive lock acquired by the update 
will prevent the second select to read the uncommitted data
because the second select will wait until the exclusive lock is
dropped because it tries to acquire a shared lock

T1 is executed first then T2

waitfor delay command helps to simulate the order of execution
so that the update is executed between the selects
and the second select to be executed after the update but before
the rollback so that the dirty read can occur
*/


--T1
set transaction isolation level read uncommitted
-- FIX: set transaction isolation level read committed
begin tran
	select * from Categories where id=1
	waitfor delay '00:00:05'
	select * from Categories where id=1
commit tran