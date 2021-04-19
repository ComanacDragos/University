SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

DBCC USEROPTIONS

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

-- reproduce the update conflict under an optimistic isolation level 


DELETE FROM Regions
INSERT INTO Regions (RegionId, Name) VALUES
(1, 'region1')

SELECT * FROM Regions

ALTER DATABASE Libraries
SET ALLOW_SNAPSHOT_ISOLATION ON

ALTER DATABASE Libraries
SET READ_COMMITTED_SNAPSHOT ON

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRAN

SELECT * FROM Regions WHERE RegionId = 1

WAITFOR DELAY '00:00:10'

UPDATE Regions
SET Name = 'update1Region'
WHERE RegionId = 1

COMMIT TRAN

