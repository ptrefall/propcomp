BEGIN TRANSACTION;

INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (1, 1, 'Eco', 1);
INSERT INTO Characters (CharacterId, UserId, Name, GameObjectId) VALUES (2, 2, 'Woody', 2);

COMMIT;
