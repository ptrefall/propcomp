BEGIN TRANSACTION;

INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (2, 1, 0, 'Tyrell');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (3, 1, 0, 'Nightwind');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (4, 1, 0, 'Sphair');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (5, 1, 0, 'Judas');
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (6, 1, 0, 'Woody');

-- SPIDER
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (11, 1, 1, 'Spider');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (11, "MeshObject");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 100, "Mesh", "WoWMaps/world/generic/gnome/passive doodads/spidertank/gnomespidertank01.m2");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 101, "Position", "3658.0f 35.8f 3648.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 101, "Scale", "1.0f 1.0f 1.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (11, 102, "Orientation", "0.70710683f 0.00000000f 0.00000000f 0.70710683f");

-- TRIGGER
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (12, 1, 1, 'Trigger');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (12, "BoxCollider");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 101, "Position", "3658.0f 37.0f 3648.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 101, "Size", "2.0f 2.0f 2.0f");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (12, "TriggerDisplayText");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 100, "DisplayTextOnEnter", "You entered the trigger");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (12, 100, "DisplayTextOnExit", "You left the trigger");

-- HOUSE
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (13, 1, 1, 'House');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (13, "MeshObject");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (13, 100, "Mesh", "Zombie/Models/Houses/Warehouse/Warehouse.cmodel");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (13, 101, "Position", "3658.0f 35.8f 3658.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (13, 101, "Scale", "0.01f 0.01f 0.01f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (13, 102, "Orientation", "0.500000 -0.500000 0.500000 0.500000");

-- HOUSE-SCAVENGE-TRIGGER
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (14, 1, 1, 'House Scavenge Trigger');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (14, "BoxCollider");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (14, 101, "Position", "3658.0f 37.0f 3648.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (14, 101, "Size", "2.0f 2.0f 2.0f");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (14, "TriggerDisplayText");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (14, 100, "DisplayTextOnEnter", "You entered the trigger");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (14, 100, "DisplayTextOnExit", "You left the trigger");

-- PLAYER ECO
INSERT INTO GameObjects (GameObjectId, GameObjectContainerId, IsActive, Description) VALUES (1, 1, 0, 'Eco');
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "MeshObject");
INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "ClickMoveController");
--INSERT INTO GameObjectComponents (GameObjectId, Type) VALUES (1, "FirstPersonMoveController");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 100, "Mesh", "WoWMaps/creature/KodoBeast/KodoBeast.m2");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 100, "MeshCreatureSkin1", "WoWMaps/creature/KodoBeast/KotoBeastWoolySkin.blp");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 100, "MeshAnimation", "4");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 101, "Position", "3648.0f 39.781879f 3648.0f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 101, "Scale", "0.1f 0.1f 0.1f");
INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 102, "BaseOrientation", "-3.0908620e-008f 0.70710683f 0.70710683f -3.0908620e-008f");
--INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 101, "DestinationPosition", "3648.0f 39.781879f 3648.0f");
--INSERT INTO GameObjectProperties (GameObjectId, Type, Name, Value) VALUES (1, 3, "MovementSpeed", "20.0f");

-- TYPE_UNSIGNED_INT = 1,
-- TYPE_INT = 2,
-- TYPE_FLOAT = 3,
-- TYPE_BOOL = 4,
-- TYPE_DOUBLE = 5,
-- TYPE_CL_STRING = 100,
-- TYPE_CL_VEC3F = 101,				// x y z
-- TYPE_CL_QUATERNIONF = 102,		// w x y z
-- TYPE_SERVERGAMEOBJECT = 1000		// id

COMMIT;
