USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
-- FIX: SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
	DECLARE @name VARCHAR(100)
	SET @name = ''

	EXEC sp_log_locks @info = 'phantom read - before select1'

	SELECT @name = @name + ' ' + Name FROM Regions
	WHERE RegionId BETWEEN 0 AND 3

	PRINT 'Read1: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'phantom read - read1', @error = NULL
	
	EXEC sp_log_locks @info = 'phantom read - between selects'

	WAITFOR DELAY '00:00:05'
	
	SET @name = ''

	EXEC sp_log_locks @info = 'phantom read - before select2'

	SELECT @name = @name + ' ' + Name FROM Regions
	WHERE RegionId BETWEEN 0 AND 3

	PRINT 'Read2: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'phantom read - read2', @error = NULL
	
	EXEC sp_log_locks @info = 'phantom read - after select2'
COMMIT TRAN
