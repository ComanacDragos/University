USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

--reproduce the following concurrency issues under pessimistic isolation 
-- levels: dirty reads, non-repeatable reads, phantom reads, and a deadlock 
-- (4 different scenarios); 
-- you can use stored procedures and / or stand-alone queries;
-- find solutions to solve / workaround the concurrency issues


SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
-- FIX: SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN

	EXEC sp_log_locks @info = 'dirty read - before select'

	DECLARE @name VARCHAR(100)

	SELECT @name = Name FROM Regions
	PRINT 'Read: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'dirty read - read', @error = NULL

	EXEC sp_log_locks @info = 'dirty read - after select'

COMMIT TRAN