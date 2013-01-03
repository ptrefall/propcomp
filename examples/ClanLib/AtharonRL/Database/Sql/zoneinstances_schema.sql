BEGIN TRANSACTION;

CREATE TABLE ZoneInstances 
(
	GameObjectContainerId INT NOT NULL,
	ZoneContinentName TEXT NOT NULL,
	ZoneInstanceName TEXT NOT NULL
);

COMMIT;
