#include "globals.h"

#define NUM_MESSAGES 24

char *menu_background;

char menu_pal[768];
char menu_cur_pal[768];

char message[NUM_MESSAGES][70] = {
"Jump 'n Bump",
"by Brainchild Design in 1998.",
"Code by Mattias Brynervall.",
"Graphics by Martin Magnusson",
"and Andreas Brynervall.",
"Music by Anders Nilsson.",
"Visit our homepage at:",
"http://www.algonet.se/~mattiasb",
"Jump 'n Bump is e-mailware.",
"That means you're supposed to send us an e-mail!",
"Write for example where you're from",
"and what you thought about this game.",
"If you do that, you will greatly encourage us",
"to make more games for you!",
"Send your e-mail to: matbr656@student.liu.se",
"Oh, and by the way, there's a lot of secrets!",
"If you can't find them, you'd better ask us...",
"If you'd like to contact a specific member of BCD,",
"these are their e-mail addresses:",
"Andreas Brynervall: andreasb@acc.umu.se",
"Mattias Brynervall: matbr656@student.liu.se",
"Martin Magnusson: marma102@student.liu.se",
"Anders Nilsson: equel@swipnet.se",
" "};


char menu(void) {
	int c1;
	char esc_pressed;
	char end_loop_flag, new_game_flag, fade_flag;
	char mod_vol, mod_fade_direction;
	int cur_message;
	int fade_dir, fade_count, fade_tick;
	char fade_pal[48];

	if (menu_init() != 0)
		return 1;

	mod_vol = 0;
	mod_fade_direction = 1;
  dj_ready_mod(MOD_MENU);
	dj_set_mod_volume(mod_vol);
	dj_set_sfx_volume(64);
  dj_start_mod();
	dj_set_nosound(0);

	memset(fade_pal, 0, 48);
	outportb(0x3c8,	240);
	for (c1 = 0; c1 < 48; c1++)
		outportb(0x3c9, fade_pal[c1]);
	fade_dir = 0;
	fade_count = 0;
	fade_tick = 0;
	cur_message = NUM_MESSAGES - 1;

 	main_info.page_info[0].num_pobs = 0;
  main_info.page_info[1].num_pobs = 0;
  main_info.view_page = 0;
  main_info.draw_page = 1;

	esc_pressed = key_pressed(1);
	end_loop_flag = new_game_flag = 0;

	while (1) {

		dj_mix();

		if (key_pressed(1) == 1 && esc_pressed == 0) {
			end_loop_flag = 1;
			new_game_flag = 0;
			memset(menu_pal, 0, 768);
			mod_fade_direction = 0;
		}
		else if (key_pressed(1) == 0)
			esc_pressed = 0;

		if (main_info.mouse_enabled == 1)
			read_mouse();
		if (main_info.joy_enabled == 1)
			read_joy();
		for (c1 = 0; c1 < 4; c1++) {
			if (end_loop_flag == 1 && new_game_flag == 1) {
				if ( (player[c1].x >> 16) >	(165 + c1 * 2) ) {
  	  		if (player[c1].x_add < 0)
  	  	 		player[c1].x_add += 16384;
    	 		else
		  	   	player[c1].x_add += 12288;
	 		    if (player[c1].x_add > 98304L)
 	  	  	 	player[c1].x_add = 98304L;
	    	  player[c1].direction = 0;
    	    if (player[c1].anim == 0) {
  	      	player[c1].anim = 1;
	          player[c1].frame = 0;
          	player[c1].frame_tick = 0;
	 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
      	  }
					player[c1].enabled = 1;
				}
		   	if ( (c1 == 0 && key_pressed(KEY_PL1_JUMP) == 0) || (c1 == 1 && key_pressed(KEY_PL2_JUMP) == 0) || (c1 == 2 && joy.but1 == 0) || (c1 == 3 && ( (main_info.num_mouse_buttons == 3 && mouse.but3 == 0) || (main_info.num_mouse_buttons == 2 && mouse.but1 == 0 && mouse.but2 == 0) ) ) ) {
		   	  if (player[c1].y_add < 0) {
  	 				player[c1].y_add += 32768;
  		  		if (player[c1].y_add > 0)
 		  				player[c1].y_add = 0;
			   	}
				}
	  	  player[c1].y_add += 12288;
  	 		if (player[c1].y_add > 36864 && player[c1].anim != 3) {
				  player[c1].anim = 3;
  	      player[c1].frame = 0;
	 	      player[c1].frame_tick = 0;
 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
      	}
	  	  player[c1].y += player[c1].y_add;
				if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
					if ( (player[c1].y >> 16) > (160 + c1 * 2) ) {
						player[c1].y = (160L + c1 * 2) << 16;
						player[c1].y_add = 0;
	     		  if (player[c1].anim != 0 && player[c1].anim != 1) {
   	 				  player[c1].anim = 0;
 		    	  	player[c1].frame = 0;
	 			      player[c1].frame_tick = 0;
 							player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
  	 	    	}
					}
				}
				else {
					if ( (player[c1].y >> 16) > (138 + c1 * 2) ) {
						player[c1].y = (138L + c1 * 2) << 16;
						player[c1].y_add = 0;
	      	  if (player[c1].anim != 0 && player[c1].anim != 1) {
     			  	player[c1].anim = 0;
  	      		player[c1].frame = 0;
	 		  	    player[c1].frame_tick = 0;
  						player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
    		    }
				   	if ( (c1 == 0 && key_pressed(KEY_PL1_JUMP) == 0) || (c1 == 1 && key_pressed(KEY_PL2_JUMP) == 0) || (c1 == 2 && joy.but1 == 0) || (c1 == 3 && ( (main_info.num_mouse_buttons == 3 && mouse.but3 == 0) || (main_info.num_mouse_buttons == 2 && mouse.but1 == 0 && mouse.but2 == 0) ) ) )
		  		  	player[c1].jump_ready = 1;
					}
				}
  	  	player[c1].x += player[c1].x_add;
				if ( (player[c1].y >> 16) >	(138 + c1 * 2) ) {
 	    		if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (190 + c1 * 2) ) {
   			  	player[c1].x = (165L + c1 * 2) << 16;
 			  	 	player[c1].x_add = 0;
		      }
 	    		if ( (player[c1].x >> 16) > (190 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
   			  	player[c1].x = (208L + c1 * 2) << 16;
 			  	 	player[c1].x_add = 0;
		      }
				}
			}
			else {
		   	if ( (c1 == 0 && key_pressed(KEY_PL1_LEFT) == 1 && key_pressed(KEY_PL1_RIGHT) == 1) || (c1 == 1 && key_pressed(KEY_PL2_LEFT) == 1 && key_pressed(KEY_PL2_RIGHT) == 1) || (c1 == 2 && joy.x < -512 && joy.x > 512) || (c1 == 3 && mouse.but1 == 1 && mouse.but2 == 1) ) {
					if (player[c1].direction == 1) {
						if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
  	  				if (player[c1].x_add > 0) {
 	   						player[c1].x_add -= 16384;
								if ( (player[c1].y >> 16) >= (160 + c1 * 2) )
 			  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
							}
 		   				else
		  			   	player[c1].x_add -= 12288;
						}
						if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
  		  			if (player[c1].x_add > 0) {
 		   					player[c1].x_add -= 16384;
								if ( (player[c1].y >> 16) >= (138 + c1 * 2) )
 		  		    		add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
							}
 		   				else
		  			   	player[c1].x_add -= 12288;
						}
 				    if (player[c1].x_add < -98304L)
 			  	   	player[c1].x_add = -98304L;
			      player[c1].direction = 1;
	        	if (player[c1].anim == 0) {
  	    	  	player[c1].anim = 1;
      	    	player[c1].frame = 0;
    	    	  player[c1].frame_tick = 0;
		 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
	    	    }
					}
					else {
						if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
 	  					if (player[c1].x_add < 0) {
 	  				 		player[c1].x_add += 16384;
								if ( (player[c1].y >> 16) >= (160 + c1 * 2) )
 			  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
							}
 		  	 			else
			  		   	player[c1].x_add += 12288;
						}
						if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
 	  					if (player[c1].x_add < 0) {
 		  			 		player[c1].x_add += 16384;
								if ( (player[c1].y >> 16) >= (138 + c1 * 2) )
		  		    		add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
							}
 		  	 			else
			  		   	player[c1].x_add += 12288;
						}
	 			    if (player[c1].x_add > 98304L)
 		  	  	 	player[c1].x_add = 98304L;
		    	  player[c1].direction = 0;
    	    	if (player[c1].anim == 0) {
  	    	  	player[c1].anim = 1;
	    	      player[c1].frame = 0;
    	      	player[c1].frame_tick = 0;
		 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
	      	  }
					}
				}
		   	else if ( (c1 == 0 && key_pressed(KEY_PL1_LEFT) == 1) || (c1 == 1 && key_pressed(KEY_PL2_LEFT) == 1) || (c1 == 2 && joy.x < -512) || (c1 == 3 && mouse.but1 == 1) ) {
					if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
  	  			if (player[c1].x_add > 0) {
 	   					player[c1].x_add -= 16384;
							if ( (player[c1].y >> 16) >= (160 + c1 * 2) )
 		  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
						}
 		   			else
		  		   	player[c1].x_add -= 12288;
					}
					if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
  	  			if (player[c1].x_add > 0) {
 	   					player[c1].x_add -= 16384;
							if ( (player[c1].y >> 16) >= (138 + c1 * 2) )
 		  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
						}
 		   			else
		  		   	player[c1].x_add -= 12288;
					}
 			    if (player[c1].x_add < -98304L)
 		  	   	player[c1].x_add = -98304L;
		      player[c1].direction = 1;
	        if (player[c1].anim == 0) {
  	      	player[c1].anim = 1;
          	player[c1].frame = 0;
        	  player[c1].frame_tick = 0;
	 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
    	    }
				}
	   		else if ( (c1 == 0 && key_pressed(KEY_PL1_RIGHT) == 1) || (c1 == 1 && key_pressed(KEY_PL2_RIGHT) == 1) || (c1 == 2 && joy.x > 512) || (c1 == 3 && mouse.but2 == 1) ) {
					if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
 	  				if (player[c1].x_add < 0) {
 	  			 		player[c1].x_add += 16384;
							if ( (player[c1].y >> 16) >= (160 + c1 * 2) )
 		  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
						}
 		  	 		else
			  	   	player[c1].x_add += 12288;
					}
					if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
 	  				if (player[c1].x_add < 0) {
 	  			 		player[c1].x_add += 16384;
							if ( (player[c1].y >> 16) >= (138 + c1 * 2) )
		  		    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
						}
 		  	 		else
			  	   	player[c1].x_add += 12288;
					}
	 		    if (player[c1].x_add > 98304L)
 	  	  	 	player[c1].x_add = 98304L;
	    	  player[c1].direction = 0;
    	    if (player[c1].anim == 0) {
  	      	player[c1].anim = 1;
	          player[c1].frame = 0;
          	player[c1].frame_tick = 0;
	 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
      	  }
				}
//  	  	if ( (c1 == 0 && ( (key_pressed(KEY_PL1_LEFT) == 0 && key_pressed(KEY_PL1_RIGHT) == 0) || (key_pressed(KEY_PL1_LEFT) == 1 && key_pressed(KEY_PL1_RIGHT) == 1) ) ) || (c1 == 1 && ( (key_pressed(KEY_PL2_LEFT) == 0 && key_pressed(KEY_PL2_RIGHT) == 0) || (key_pressed(KEY_PL2_LEFT) == 1 && key_pressed(KEY_PL2_RIGHT) == 1) ) ) || (c1 == 2 && ( (joy.x >= -512 && joy.x <= 512) || (joy.x < -512 && joy.x > 512) ) ) || (c1 == 3 && ( (mouse.but1 == 0 && mouse.but2 == 0) || (mouse.but1 == 1 && mouse.but2 == 1) ) ) ) {
				else {
					if ( ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) && (player[c1].y >> 16) >= (160 + c1 * 2) ) {
	    	 		if (player[c1].x_add < 0) {
 	  		  		player[c1].x_add += 16384;
  				    if (player[c1].x_add > 0)
	 	 		  	  	player[c1].x_add = 0;
 		  	    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
		      	}
	      		else if (player[c1].x_add > 0) {
   			  		player[c1].x_add -= 16384;
 	 		  		  if (player[c1].x_add < 0)
  		  	  		player[c1].x_add = 0;
 			 	    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
			 	    }
					}
					if ( ( ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) && (player[c1].y >> 16) >= (138 + c1 * 2) ) ) {
	    	 		if (player[c1].x_add < 0) {
 	  		  		player[c1].x_add += 16384;
  				    if (player[c1].x_add > 0)
	 	 		  	  	player[c1].x_add = 0;
 		  	    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
		      	}
	      		else if (player[c1].x_add > 0) {
   			  		player[c1].x_add -= 16384;
 	 		  		  if (player[c1].x_add < 0)
  	 	  	  		player[c1].x_add = 0;
 		  	    	add_object(OBJ_SMOKE, (player[c1].x >> 16) + 2 + rnd(9), (player[c1].y >> 16) + 13 + rnd(5), 0, -16384 - rnd(8192), OBJ_ANIM_SMOKE, 0);
		  	    }
					}
  	      if (player[c1].anim == 1) {
	        	player[c1].anim = 0;
          	player[c1].frame = 0;
        	  player[c1].frame_tick = 0;
  					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
    	    }
				}
	   		if (player[c1].jump_ready == 1 && ( (c1 == 0 && key_pressed(KEY_PL1_JUMP) == 1) || (c1 == 1 && key_pressed(KEY_PL2_JUMP) == 1) || (c1 == 2 && joy.but1 == 1)  || (c1 == 3 && ( (main_info.num_mouse_buttons == 3 && mouse.but3 == 1) || (main_info.num_mouse_buttons == 2 && mouse.but1 == 1 && mouse.but2 == 1) ) ) ) ) {
					if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
						if ( (player[c1].y >> 16) >= (160 + c1 * 2) ) {
		   	  	 	player[c1].y_add = -280000L;
    	  		 	player[c1].anim = 2;
 				      player[c1].frame = 0;
			   	    player[c1].frame_tick = 0;
							player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
 	  					player[c1].jump_ready = 0;
							dj_play_sfx(SFX_JUMP, SFX_JUMP_FREQ + rnd(2000) - 1000, 64, 0, 0, -1);
						}
					}
					else {
						if ( (player[c1].y >> 16) >= (138 + c1 * 2) ) {
		   	  	 	player[c1].y_add = -280000L;
    	  		 	player[c1].anim = 2;
 				      player[c1].frame = 0;
			   	    player[c1].frame_tick = 0;
							player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
 	  					player[c1].jump_ready = 0;
							dj_play_sfx(SFX_JUMP, SFX_JUMP_FREQ + rnd(2000) - 1000, 64, 0, 0, -1);
						}
					}
				}
		   	if ( (c1 == 0 && key_pressed(KEY_PL1_JUMP) == 0) || (c1 == 1 && key_pressed(KEY_PL2_JUMP) == 0) || (c1 == 2 && joy.but1 == 0) || (c1 == 3 && ( (main_info.num_mouse_buttons == 3 && mouse.but3 == 0) || (main_info.num_mouse_buttons == 2 && mouse.but1 == 0 && mouse.but2 == 0) ) ) ) {
		   	  if (player[c1].y_add < 0) {
  	 				player[c1].y_add += 32768;
  		  		if (player[c1].y_add > 0)
 		  				player[c1].y_add = 0;
			   	}
				}
	  	 	if ( (c1 == 0 && key_pressed(KEY_PL1_JUMP) == 0) || (c1 == 1 && key_pressed(KEY_PL2_JUMP) == 0) || (c1 == 2 && joy.but1 == 0) || (c1 == 3 && ( (main_info.num_mouse_buttons == 3 && mouse.but3 == 0) || (main_info.num_mouse_buttons == 2 && (mouse.but1 == 0 || mouse.but2 == 0) ) ) ) )
 			  	player[c1].jump_ready = 1;
	  	  player[c1].y_add += 12288;
  	 		if (player[c1].y_add > 36864 && player[c1].anim != 3) {
				  player[c1].anim = 3;
  	      player[c1].frame = 0;
	 	      player[c1].frame_tick = 0;
 					player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
      	}
	  	  player[c1].y += player[c1].y_add;
				if ( (player[c1].x >> 16) <= (165 + c1 * 2) || (player[c1].x >> 16) >= (208 + c1 * 2) ) {
					if ( (player[c1].y >> 16) > (160 + c1 * 2) ) {
						player[c1].y = (160L + c1 * 2) << 16;
						player[c1].y_add = 0;
      		  if (player[c1].anim != 0 && player[c1].anim != 1) {
    	 			  player[c1].anim = 0;
  		      	player[c1].frame = 0;
		 		      player[c1].frame_tick = 0;
  						player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
//							dj_play_sfx(SFX_LAND, SFX_LAND_FREQ, 64, 0, 0, -1);
    	    	}
					}
				}
				else {
					if ( (player[c1].y >> 16) > (138 + c1 * 2) ) {
						player[c1].y = (138L + c1 * 2) << 16;
						player[c1].y_add = 0;
	      	  if (player[c1].anim != 0 && player[c1].anim != 1) {
     			  	player[c1].anim = 0;
  	      		player[c1].frame = 0;
	 		  	    player[c1].frame_tick = 0;
  						player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
//							dj_play_sfx(SFX_LAND, SFX_LAND_FREQ, 64, 0, 0, -1);
    		    }
					}
				}
  	  	player[c1].x += player[c1].x_add;
	 	    if ( (player[c1].x >> 16) < 0) {
   	  		player[c1].x = 0;
 	  		 	player[c1].x_add = 0;
  	    }
	 	    if ( (player[c1].x >> 16) > 400) {
					end_loop_flag = 1;
					new_game_flag = 1;
					memset(menu_pal, 0, 768);
					mod_fade_direction = 0;
  	    }
				if ( (player[c1].y >> 16) >	(138 + c1 * 2) ) {
 	    		if ( (player[c1].x >> 16) > (165 + c1 * 2) && (player[c1].x >> 16) < (190 + c1 * 2) ) {
   			  	player[c1].x = (165L + c1 * 2) << 16;
 			  	 	player[c1].x_add = 0;
		      }
 	    		if ( (player[c1].x >> 16) > (190 + c1 * 2) && (player[c1].x >> 16) < (208 + c1 * 2) ) {
   			  	player[c1].x = (208L + c1 * 2) << 16;
 			  	 	player[c1].x_add = 0;
		      }
				}
			}
  	 	player[c1].frame_tick++;
 	    if (player[c1].frame_tick >= player_anims[player[c1].anim].frame[player[c1].frame].ticks) {
      	player[c1].frame++;
   			if (player[c1].frame >= player_anims[player[c1].anim].num_frames)
			  	player[c1].frame = player_anims[player[c1].anim].restart_frame;
	      player[c1].frame_tick = 0;
      }
			player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image + player[c1].direction * 9;
		}

		dj_mix();

    main_info.page_info[main_info.draw_page].num_pobs = 0;

		for (c1 = 3; c1 >= 0; c1--)
			add_pob(main_info.draw_page, player[c1].x >> 16, player[c1].y >> 16, player[c1].image + c1 * 18, rabbit_gobs);

    update_objects();

		draw_pobs(main_info.draw_page);

		dj_mix();

		if (mod_fade_direction == 1) {
			if (mod_vol < 35) {
				mod_vol++;
				dj_set_mod_volume(mod_vol);
			}
		}
		else {
			if (mod_vol > 0) {
				mod_vol--;
				dj_set_mod_volume(mod_vol);
			}
		}

		fade_flag = 0;
		for (c1 = 0; c1 < 720; c1++) {
			if (menu_cur_pal[c1] < menu_pal[c1]) {
				menu_cur_pal[c1]++;
				fade_flag = 1;
			}
			else if (menu_cur_pal[c1] > menu_pal[c1]) {
				menu_cur_pal[c1]--;
				fade_flag = 2;
			}
		}
		if (fade_flag == 0 && end_loop_flag == 1) {
			menu_deinit();
			if (new_game_flag == 1)
				return 0;
			else
				return 1;
		}

/*		if (fade_flag == 2) {
			fade_dir = 0;
			fade_count = 0;
		}*/

		switch (fade_dir) {
			case 0:
				if (fade_count < 30) {
					for (c1 = 0; c1 < 48; c1++) {
						if (fade_pal[c1] > 0)
							fade_pal[c1]--;
					}
					fade_count++;
				}
				else {
					outportw(0x3c4, 0x0f02);
				  memset( (char *)(0xa0000 + 220 * 100 + __djgpp_conventional_base), 0, 2000);
				  memset( (char *)(0xa0000 + 32768 + 220 * 100 + __djgpp_conventional_base), 0, 2000);
					cur_message++;
					if (cur_message >= NUM_MESSAGES)
						cur_message -= NUM_MESSAGES;
					put_text(0, 200, 220, message[cur_message], 2);
					put_text(1, 200, 220, message[cur_message], 2);
					fade_dir = 1;
					fade_count = 0;
					fade_tick = 0;
				}
				break;
			case 1:
				if (fade_count < 100) {
					for (c1 = 0; c1 < 48; c1++) {
						if (fade_pal[c1] < menu_pal[c1 + 720])
							fade_pal[c1]++;
					}
					fade_count++;
				}
				else {
					fade_dir = 0;
					fade_count = 0;
					fade_tick = 0;
				}
				break;
		}

		for (c1 = 0; c1 < 48; c1++) {
			if (fade_pal[c1] > menu_pal[c1 + 720])
				fade_pal[c1]--;
		}

    main_info.draw_page ^= 1;
    main_info.view_page ^= 1;

		outportw(0x3d4, (main_info.view_page << 23) + 0x0d);
		outportw(0x3d4, ( (main_info.view_page << 15) & 0xff00) + 0x0c);

	 	while( (inportb(0x3da) & 8) == 0)
			dj_mix();
		while( (inportb(0x3da) & 8) == 8)
			dj_mix();

		if (fade_flag != 0) {
	  	outportb(0x3c8, 0);
 			for (c1 = 0; c1 < 720; c1++)
		 		outportb(0x3c9, menu_cur_pal[c1]);
		}

  	outportb(0x3c8, 240);
		for (c1 = 0; c1 < 48; c1++)
	 		outportb(0x3c9, fade_pal[c1]);

		dj_mix();

		redraw_pob_backgrounds(main_info.draw_page);

	}

	menu_deinit();
	return 0;

}


char menu_init(void) {
	FILE *handle;
	int c1;

  outportb(0x3c8, 0);
 	for (c1 = 0; c1 < 768; c1++)
 		outportb(0x3c9, 0);

  if ( (handle = dat_open("menu.pcx", datfile_name, "rb") ) == 0) {
		strcpy(main_info.error_str, "Error loading 'menu.pcx', aborting...\n");
		return 1;
	}
	if (read_pcx(handle, background_pic, 102400, menu_pal) != 0) {
		strcpy(main_info.error_str, "Error loading 'menu.pcx', aborting...\n");
		return 1;
	}
	fclose(handle);
  if ( (handle = dat_open("menumask.pcx", datfile_name, "rb") ) == 0) {
		strcpy(main_info.error_str, "Error loading 'menumask.pcx', aborting...\n");
		return 1;
	}
	if (read_pcx(handle, mask_pic, 102400, 0) != 0) {
		strcpy(main_info.error_str, "Error loading 'menumask.pcx', aborting...\n");
		return 1;
	}
	fclose(handle);
	memset(menu_cur_pal, 0, 768);

	put_block(0, 0, 0, 400, 256, background_pic);
	put_block(1, 0, 0, 400, 256, background_pic);

	for (c1 = 0; c1 < 4; c1++) {
		player[c1].enabled = 0;
		player[c1].x = (long)rnd(150) << 16;
		player[c1].y = (160L + c1 * 2) << 16;
		player[c1].x_add = 0;
		player[c1].y_add = 0;
		player[c1].direction = rnd(2);
		player[c1].jump_ready = 1;
		player[c1].anim = 0;
		player[c1].frame = 0;
		player[c1].frame_tick = 0;
    player[c1].image = player_anims[player[c1].anim].frame[player[c1].frame].image;
	}

	for (c1 = 0; c1 <	300; c1++)
		objects[c1].used = 0;

 	main_info.page_info[0].num_pobs = 0;
  main_info.page_info[1].num_pobs = 0;

	return 0;

}


void menu_deinit(void) {

	dj_set_nosound(1);

}

