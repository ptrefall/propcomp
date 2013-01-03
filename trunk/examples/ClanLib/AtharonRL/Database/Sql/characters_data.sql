BEGIN TRANSACTION;

INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (1, 1, 'Eco', 1);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (2, 1, 'Tyrell', 2);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (3, 1, 'Nightwind', 3);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (4, 1, 'Sphair', 4);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (5, 1, 'Judas', 5);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (6, 2, 'Woody', 6);

COMMIT;
