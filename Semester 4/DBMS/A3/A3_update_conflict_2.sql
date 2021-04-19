SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

DBCC USEROPTIONS

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

-- reproduce the update conflict under an optimistic isolation level 

BEGIN TRAN

UPDATE Regions
SET Name = 'update1Region'
WHERE RegionId = 1

WAITFOR DELAY '00:00:10'

COMMIT TRAN
