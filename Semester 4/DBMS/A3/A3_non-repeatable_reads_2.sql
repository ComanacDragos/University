USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

SET TRANSACTION ISOLATION LEVEL READ COMMITTED
-- FIX: SET TRANSACTION ISOLATION LEVEL REPEATABLE READ

BEGIN TRAN
	SELECT * FROM Regions
	WAITFOR DELAY '00:00:05'
	SELECT * FROM Regions
COMMIT TRAN