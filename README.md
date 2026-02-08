# tiny-big-islands-of-joris
Sandbox game written in C++

## References
* Using SDL2
* Using SDL2_Image

### Tutorial used
* https://www.youtube.com/watch?v=agn8GqGrCj4&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=7
* https://www.youtube.com/watch?v=_45s_gNicwo&list=PLAGy_slICtV1AD8nV3nEe7P8j82XdxH-7
* https://www.youtube.com/watch?v=hBwhiaxLAJM

# TODO List
- [ ] Crear un Terraria Like
- [ ] Game Loop System
  - [x] Crear Update con delta
  - [ ] Crear PhysicsUpdate con delta
- [ ] Sistema de inventario
  - [ ] Personaje tendrá una máximo de 50 objetos diferentes
- [ ] Sistema de equipamiento
- [ ] Sistema de niveles de personajes (opcionalmente)
- [ ] Sistema de clases / Jobs
  - [ ] Melee (Llamado Reaper)
  - [ ] Ranged (Llamado Scout)
  - [ ] Healer (Llamado Bishop)
  - [ ] Mage (Llamado Sage)
  - [ ] Summoner (Llamado Artificer)
- [ ] Sistema de cofres
  - [ ] Intentar optimizar en caso de que sucedan errores con esto
  - [ ] Máximo de 40 objetos diferentes
- [ ] Sistema de Tilemaps
  - [ ] Verificar si se puede hacer Dual TileMaps

## GUI
- [ ] Pixel Art Game
- [ ] Main Menu
  - [ ] Background animado (Si no es posible, será estático)
- [ ] Inventario
- [ ] Pausa
- [ ] Settings

## Rendering
- [ ] Rendering system
  - [ ] Shaders:
  	- [ ] Animated nice water
	- [ ] No visual artifacts on textures
	- [ ] PBR pipeline
	- [ ] Lights
  	- [ ] Lights stored in cube maps
	- [ ] Sky Box reflection
	- [ ] SSR
	- [ ] HBAO / SSAO
	- [ ] HDR, ACES tone mapping
	- [ ] Bloom
	- [ ] Automatic exposure
	- [ ] Lens flare
	- [ ] Color grading
	- [ ] Fog -(todo improve)
	- [ ] Underwater fog -(todo improve)
	- [ ] God rays	
	- [ ] Fake Shadows for all light types
  	- [ ] Shadows
   	- [ ] Cascaded shadow maps
	- [ ] Depth of field (maybe blur far stuff)
  - [ ] Use the same shader for all things in game

## Multiplayer
- [ ] Aprender a cómo crear multiplayer, basado en buffers, sincronización.
- [ ] Multi player
  - [ ] Connection to server and handshake
  - [ ] Syncronization
  - [ ] Server can validate moves
  - [ ] Server knows player position to optimize chunk logic stuff
  - [ ] Undo Stuff On client
  - [ ] Buffering
  - [ ] Rubber banding
  - [ ] Entities 

## Lore
- [ ] Juego sobre hadas de 6 brazos
  - [ ] 16 Razas (Empezar con 2, uno de cada categoría)
    - [ ] 8 Hadas planta
    - [ ] 8 Hadas esporas (hongos)
