USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

SET TRANSACTION ISOLATION LEVEL READ COMMITTED
-- FIX: SET TRANSACTION ISOLATION LEVEL REPEATABLE READ

BEGIN TRAN
	DECLARE @name VARCHAR(100)

	EXEC sp_log_locks @info = 'non-repeatable read - before select1'

	SELECT @name = Name FROM Regions
	PRINT 'Read1: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'non-repeatable read - read1', @error = NULL

	EXEC sp_log_locks @info = 'non-repeatable read - between selects'

	WAITFOR DELAY '00:00:05'
	
	SELECT @name = Name FROM Regions
	PRINT 'Read2: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'non-repeatable read - read2', @error = NULL

	EXEC sp_log_locks @info = 'non-repeatable read - after select2'

COMMIT TRAN