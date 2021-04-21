SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

DBCC USEROPTIONS

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

-- reproduce the update conflict under an optimistic isolation level 

BEGIN TRAN
	EXEC sp_log_locks @info = 'update conflict2 - before update'
	
	UPDATE Regions
	SET Name = 'update2Region'
	OUTPUT GETDATE(), 'update conflict2 - update', deleted.Name, inserted.Name, NULL
	INTO ChangesLog
	WHERE RegionId = 1

	WAITFOR DELAY '00:00:10'

	EXEC sp_log_locks @info = 'update conflict2 - after update'
COMMIT TRAN
