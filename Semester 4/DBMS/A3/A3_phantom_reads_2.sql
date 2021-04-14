USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
-- FIX: SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
	SELECT * FROM Regions
	WHERE RegionId BETWEEN 0 AND 3
	
	WAITFOR DELAY '00:00:05'
	
	SELECT * FROM Regions
	WHERE RegionId BETWEEN 0 AND 3
COMMIT TRAN
