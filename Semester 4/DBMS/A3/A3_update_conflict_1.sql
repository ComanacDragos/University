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

SELECT * FROM ChangesLog
ORDER BY currentTime
SELECT * FROM LocksLog
ORDER BY currentTime DESC

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRAN
	DECLARE @name VARCHAR(100)

	EXEC sp_log_locks @info = 'update conflict1 - brefore select'

	SELECT @name = Name FROM Regions
	WHERE RegionId = 1
	PRINT 'Read1: ' + @name
	EXEC sp_log_changes @oldData = NULL, @newData = @name, @info = 'non-repeatable read - read1', @error = NULL

	EXEC sp_log_locks @info = 'update conflict1 - between select and update'
	WAITFOR DELAY '00:00:10'

	UPDATE Regions
	SET Name = 'update1Region'
	OUTPUT GETDATE(), 'upadte confilct1 - update', deleted.Name, inserted.Name, NULL
	INTO ChangesLog
	WHERE RegionId = 1

	EXEC sp_log_locks @info = 'update conflict1 - after update'
COMMIT TRAN

