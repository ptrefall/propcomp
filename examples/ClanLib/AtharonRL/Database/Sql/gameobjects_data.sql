BEGIN TRANSACTION;

INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (2, 1, 0, 'Tyrell');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (3, 1, 0, 'Nightwind');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (4, 1, 0, 'Sphair');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (5, 1, 0, 'Judas');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (6, 1, 0, 'Woody');

-- SPIDER
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (11, 1, 1, 'Orc');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (11, "Monster");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 6, 	"Character", "o");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 101, "Position", "10 10");

-- TRIGGER
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (12, 1, 1, 'Trigger');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (12, "Collider");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 101, "Position", "15 2");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (12, "TriggerDisplayText");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 100, "DisplayTextOnEnter", "You entered the trigger");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 100, "DisplayTextOnExit", "You left the trigger");

-- PLAYER ECO
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (1, 1, 0, 'Eco');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "Monster");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "ClickMoveController");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "NumpadMoveController");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 6, 	"Character", "@");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 101, 	"Position", "12 15");

-- TYPE_UNSIGNED_INT = 1,
-- TYPE_INT = 2,
-- TYPE_FLOAT = 3,
-- TYPE_BOOL = 4,
-- TYPE_DOUBLE = 5,
-- TYPE_CHAR = 6,
-- TYPE_CL_STRING = 100,
-- TYPE_CL_VEC2I = 101,				// x y z
-- TYPE_SERVERGAMEOBJECT = 1000		// id

COMMIT;
