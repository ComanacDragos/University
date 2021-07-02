use PracticalExam
go

select * from Categories


--T2
begin tran
	update Categories set description='dirty read' where id=1
	waitfor delay '00:00:05'
rollback
