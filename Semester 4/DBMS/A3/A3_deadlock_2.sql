SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

-- SET DEADLOCK_PRIORITY HIGH
-- SET DEADLOCK_PRIORITY LOW

BEGIN TRAN
	UPDATE Cities
	SET CityName = 'deadlockCity1'
	WHERE CityId = 1
	
	WAITFOR DELAY '00:00:05'
	
	UPDATE Regions
	SET Name = 'deadlockRegion2'
	WHERE RegionId = 1

COMMIT TRAN
