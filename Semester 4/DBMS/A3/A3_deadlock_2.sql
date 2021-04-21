SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

-- SET DEADLOCK_PRIORITY HIGH
-- SET DEADLOCK_PRIORITY LOW

BEGIN TRAN
	EXEC sp_log_locks @info = 'deadlock2 - before update'
	UPDATE Cities
	SET CityName = 'deadlockCity2'
	OUTPUT GETDATE(), 'deadlock2 - update', deleted.CityName, inserted.CityName, NULL
	INTO ChangesLog
	WHERE CityId = 1
	
	EXEC sp_log_locks @info = 'deadlock2 - between update'
	WAITFOR DELAY '00:00:05'
	
	UPDATE Regions
	SET Name = 'deadlockRegion2'
	OUTPUT GETDATE(), 'deadlock2 - update', deleted.Name, inserted.Name, NULL
	INTO ChangesLog
	WHERE RegionId = 1

	EXEC sp_log_locks @info = 'deadlock2 - after update'
COMMIT TRAN
