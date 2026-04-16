*This project has been created as part of the 42 curriculum by [mcolin](https://profile-v3.intra.42.fr/users/mcolin), [ykolacze](https://profile-v3.intra.42.fr/users/ykolacze).*

# PROJECT [42](https://42.fr/en/homepage/) : cub3D >_

This project is inspired by the world-famous [Wolfenstein 3D game](https://fr.wikipedia.org/wiki/Wolfenstein_3D), which is considered the first FPS ever created.

## 📖 Description [**cub3D**](https://cdn.intra.42.fr/pdf/pdf/198996/en.subject.pdf)

This project’s will enable to explore ray-casting. Goal will be to make a dynamic view inside a maze.
Objectives are similar to all this first year’s objectives: rigor, use of C, basic algorithms, information research, etc.
As a graphic design project, cub3D will enable to improve skills in these areas: windows, colors, events, fill shapes, etc.
In conclusion, cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics.

## 🧠 what we have learned

- Undertsand the mathematics, applies to raycasting and how to apply it in algorithms.

- Understand [MacroLibX](https://macrolibx.kbz8.me/)

## 📜 None of this would have been possible without you. Thank you.

[rprieur](https://profile-v3.intra.42.fr/users/rprieur): 👑 Thank you for all the hours spent helping us! 🐐

## 🌳 Tree

<details>
<summary><h2>show</h2></summary>

```txt
|-- MacroLibX
|-- Makefile
|-- README.md
|-- assets
|   `-- textures
|       |-- ea.png
|       |-- east.png
|       |-- no.png
|       |-- north.png
|       |-- so.png
|       |-- south.png
|       |-- we.png
|       |-- west.png
|       `-- wolftextures.png
|-- includes
|   |-- cub.h
|   |-- dda.h
|   |-- draw.h
|   |-- error.h
|   |-- event.h
|   |-- get_ceil_floor.h
|   |-- get_map.h
|   |-- get_scene.h
|   |-- get_texture.h
|   |-- init_mlx.h
|   |-- overlay.h
|   |-- player_movement.h
|   |-- player_movement_bonus.h
|   |-- raycasting.h
|   `-- set_map.h
|-- libft
|-- maps
|   `-- test.cub
`-- srcs
    |-- cub3d.c
    |-- dda.c
    |-- draw.c
    |-- error.c
    |-- event
    |   |-- event.c
    |   |-- player_movement.c
    |   `-- player_movement_bonus.c
    |-- init_mlx.c
    |-- overlay
    |   `-- overlay.c
    |-- parsing
    |   |-- get_ceil_floor.c
    |   |-- get_map.c
    |   |-- get_scene.c
    |   |-- get_texture.c
    |   `-- set_map.c
    `-- raycasting.c
```
</details>

## 📌 Instructions

We use the folowing flags to compile the project: cc -MP -MMD -Wall -Werror -Wextra -g

- make (doing the mandatory project cub3D).
- make bonus (doing the bonus project cub3D_bonus).
- make clean (clean objects directories an files).
- make fclean (clean all).
- make re (clean all and remake).

## 🛠️ Commands

### How to run it
The program should be executed as follows:
```txt
./cub3D path_to_your_scene_description.cub
```
It should launch a window with the maze.

<details>
<summary><h2>Valgrind</h2></summary>

You can use these valgrind options to check for leaks and to suppress some leaks from MacroLibX:

```txt
valgrind --leak-check=full --show-leak-kinds=all --suppressions=./MacroLibX/valgrind.supp
```

</details>

## ℹ️ Ressources

[Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)

[Wikipédia](https://fr.wikipedia.org/wiki/Wikip%C3%A9dia:Accueil_principal)

[Lot's of Romain!!! <3 <3 <3](https://profile-v3.intra.42.fr/users/rprieur)

[MacroLibX tutorial](https://macrolibx.kbz8.me/guides/getting_started/)

We tried using ChatGPT to get help with the `mlx_put_transformed_image_to_window` function, but without success. In the end, Romain stepped in, explained everything clearly, and resolved the issue not only quickly but also with concrete accuracy—unlike ChatGPT. Thanks to peer-to-peer support. Long live 42.

We asked chatGPT to re-modify this previous sentence for us, which it did perfectly. The moral of the story is, AI is still a tool.

## conclusion

This project has introduce us i the world of graphic, it was really difficult but we did it.
We could even say: not the world but the universe !!!<br>