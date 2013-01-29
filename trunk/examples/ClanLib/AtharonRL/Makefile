CXXFLAGS = -g -I . `pkg-config --cflags clanDisplay-3.0 clanCore-3.0 clanApp-3.0 clanSqlite-3.0 clanNetwork-3.0`
libs = `pkg-config --libs clanDisplay-3.0 clanCore-3.0 clanApp-3.0 clanSqlite-2.4 clanNetwork-3.0` -lpthread -ldl

Server = \
	Server/main.o \
	Server/precomp.o \
	Server/service.o \
	Server/server.o \
	Server/server_user.o \
	Server/service.o \
	Server/Database/database_characters.o \
	Server/Database/database_email.o \
	Server/Database/database_gameobject_containers.o \
	Server/Database/database_gameobjects.o \
	Server/Database/database_users.o \
	Server/Database/database_zone_instances.o \
	Server/GameWorld/character.o \
	Server/GameWorld/character_manager.o \
	Server/GameWorld/component_factory.o \
	Server/GameWorld/gameobject_container.o \
	Server/GameWorld/player.o \
	Server/GameWorld/player_manager.o \
	Server/GameWorld/replicated_component.o \
	Server/GameWorld/server_gameobject.o \
	Server/GameWorld/Components/network_receiver.o \
	Server/GameWorld/Components/server_transform.o \
	Server/GameWorld/Components/server_visual.o \
	Server/GameWorld/Netevents/netevents_character.o \
	Server/GameWorld/Netevents/netevents_player.o \
	Server/GameWorld/Zone/zone.o \
	Server/GameWorld/Zone/zone_architect.o \
	Server/GameWorld/Zone/zone_manager.o \
	Server/GameWorld/Zone/zone_map.o \
	Server/GameWorld/Zone/zone_map_section.o \
	Server/GameWorld/Zone/zone_player_manager.o \
	Server/GameWorld/Zone/zone_vicinity_map.o \
	Server/GameWorld/Zone/zone_vicinity_objects.o \
	Server/GameWorld/Zones/dungeon.o \
	Server/GameWorld/Zones/dungeon_level.o \
	Server/GameWorld/Zones/town.o

Engine = \
	Server/precomp.o
	
all: server

clean:
	rm server `find . -name *.o`

COMPILE.cxx = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
OUTPUT_OPTION = -o $@

%.o: %.cxx
	$(COMPILE.cxx) $< $(OUTPUT_OPTION)

server: $(Server) $(Engine)
	g++ -o server $(Server) $Engine) $(libs)
	echo All done
