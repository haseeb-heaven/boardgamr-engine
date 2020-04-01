![cover_logo](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/cover_logo.jpg?raw=true "")

**_Board-Gamr_** is **[Game Engine](https://en.wikipedia.org/wiki/Game_engine)** to make **console** board games in **c/c++** it provide all the necessary methods to make simple game using
only _ASCII_ characters It provides various types of **Board,game Cards,Dice and Player modules**.
It works with all OS **Windows,Mac,Linux** etc because it used only _standard_ header files.

**NOTE** : This game engine doesnt provide any **GUI** and works with console **CLI** based games.
 
**AIM** : The aim of this engine is only to provide the most efficient way of creating **board games** with pure c/c++ **(no _3rd_ party library required)**
and with portability to any OS **_(Windows,Mac,Linux)._**

## **_Your support is needed to keep this project alive, Feel free to donate._**
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.me/haseebmir91)


**_FEATURES_** : </br>
1)**Fast and flexible** modules and methods to create **board/player,cards** and more.</br>
2)**_Board_** module to access,manipulate game boards easily by **row/columns/diagonals** etc.</br>
3)**_Player_** module to access,manipulate player's **position/character** easily.</br>
4)**_Card_** module to **add/remove/shuffle/draw** game cards easily with **automatic deck management**.</br>
5)**_Dice_** module to manage game **die/dices and coins** easily.</br>
6)**_Time_** module to manage game **time** easily.</br>
7)**_Font_** module to draw **fonts** that supports _FIGlet_ fonts with no **external dependency**.</br>
8)**Inbuilt tools** for converting/filling all type of arrays.</br>
9)**Adanced** memory efficient design by selecting _specific module_ at **compile time**.</br>
10)**Portable** Game engine works any **OS (Windows,Mac,Linux)** with pure _c/c++_ **(no 3rd party library required)**.</br>


# How to import any module :

## Using specific module.
Using this format of macro **_USE_%MODULE-NAME%_MODULE_** example _USE_BOARD_MODULE_.</br>
![use_module](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/use_module.jpg?raw=true "")

## Using all modules.
Use macro _USE_ALL_MODULES_ to import all modules.</br>
![use_all_modules](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/use_all_modules.jpg?raw=true "")

# Engine Modules :

# Board Module :

## Init/Drawing various game boards : 

Using **BG_InitGameBoard()** and **BG_DrawGameBoard()** methods.

_Alternate game board_</br>
![alt_game_board](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/alt_game_board.jpg?raw=true "")

_Sequential game board_</br>
![seq_game_board](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/seq_game_board.jpg?raw=true "")


## Filling data in game board by rows/cols/diagonals : 

Using **BG_FillBoardRow(),BG_FillBoardCol(),BG_FillBoardDiagonals()** methods.

_Game data by row_.</br>
![fill_row](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/fill_row.jpg?raw=true "")

_Game data by column_.</br>
![fill_cols](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/fill_cols.jpg?raw=true "")

_Game data by left/rightdiagonals_.</br>
![fill_left_diag](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/fill_left_diag.jpg?raw=true "")
![fill_right_diag](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/fill_right_diag.jpg?raw=true "")

## Get information about game board : 

Using **BG_GetBoardInfo(),BG_GetPieceInfo()** methods.
_Get board information_.</br>
![get_board_info](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/get_board_info.jpg?raw=true "")

# Card Module :

## Get/draw deck of cards : 

**QUARTER-DECK** Using **BG_DrawDeck() and BG_DrawDeck()** methods.</br>
![quarter_deck](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/quarter_deck.jpg?raw=true "")

**HALF-DECK** Using **BG_GetHalfDeck() and BG_DrawDeck()** methods.</br>
![half_deck](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/half_deck.jpg?raw=true "")

**FULL-DECK** Using **BG_GetFullDeck() and BG_DrawDeck()** methods.</br>
![full_deck](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/full_deck.jpg?raw=true "")

**RAND-DECK** Using **BG_GetRandDeck() and BG_DrawDeck()** methods.</br>
![rand_deck](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/rand_deck.jpg?raw=true "")

## Add/Remove/Move/Copy/Shuffle cards : 

**ADDING-CARDS** Using **BG_AddCard(),BG_AddCards()** methods.</br>
![add_card](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/add_card.jpg?raw=true "")

**REMOVING-CARDS** Using **BG_RemoveCard(),BG_RemoveCards()** methods.</br>
![remove_card](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/remove_card.jpg?raw=true "")

**MOVING-CARDS** Using **BG_MoveCards()** method.</br>
![move_cards](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/move_cards.jpg?raw=true "")

**COPYING-CARDS** Using **BG_CopyCards()** method.</br>
![copy_cards](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/copy_cards.jpg?raw=true "")

**SHUFFLE-DECK** Using **BG_ShuffleDeck()** method.</br>
![shuffle_deck](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/shuffle_deck.jpg?raw=true "")


# Player Module :

## Get player turns : 

**PLAYER-TURNS** Using **BG_GetPlayerTurn()** method.</br>
![player_turn](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/player_turn.jpg?raw=true "")

**RAND-TURNS** Using **BG_GetRandTurn()** method.</br>
![rand_turn](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/rand_turn.jpg?raw=true "")

## Get player position/percent : 

**PLAYER-POSITION** Using **BG_GetRandPosition()** method.</br>
![rand_pos](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/rand_pos.jpg?raw=true "")

**PLAYER-PERCENT** Using **BG_GetScorePercent()** method.</br>
![score_percent](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/score_percent.jpg?raw=true "")


# Dice Module :

## Roll dices/coins : 

**ROLL-DICE** Using **BG_RollDie(),BG_RollDice()** methods.</br>
![roll_die](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/roll_die.jpg?raw=true "")
![roll_dice](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/roll_dice.jpg?raw=true "")

**FLIP-COIN** Using **BG_FlipCoin()** method.</br>
![flip_coin](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/flip_coin.jpg?raw=true "")

# Fonts Module :

## Drawing text in various fonts : 

**FONT-TEXT** Using **BG_DrawFont(),BG_DrawFontEx()** methods.</br>
![font_slant](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_slant.jpg?raw=true "")

**FONT-DEFAULT** Using **BG_DrawFontDefault(),BG_DrawFontEx()** methods.</br>
![font_default](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_default.jpg?raw=true "")
![font_default_allign](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_default_allign.jpg?raw=true "")

**FONT-WIDTH-ALLIGN** Using **BG_DrawFontArgs()** method.</br>
![font_args](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_args.jpg?raw=true "")

**FONT-WIDTH-ALLIGN-WITH-ARGS** Using **BG_DrawFontVargs(),BG_DrawFontVargsEx()** methods.</br>
![font_vargs](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_vargs.jpg?raw=true "")

**FONT-RIGHT-TO-LEFT** Using **BG_DrawFontRTL()** method.</br>
![font_rtl](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/font_rtl.jpg?raw=true "")


# Time Module :

## Start/Stop/Delay time : 

**START-STOP-TIME** Using **BG_StartTime(),BG_StopTime()** methods.</br>
![timer_start_stop](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/timer_start_stop.jpg?raw=true "")

**DELAY-TIME** Using **BG_TimeDelay()** method.</br>
![time_delay](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/time_delay.jpg?raw=true "")

# Misc Module :

## Fill/Convert Arrays. : 

**FILL-ARRAYS** Using **BG_FillArray()** method.</br>
![fill_array](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/fill_array.jpg?raw=true "")

**CONVERT-ARRAYS** Using **BG_ConvertArray()** method.</br>
![convert_array](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/convert_array.jpg?raw=true "")

## Generate random and clear console screen : 

**RANDOM-GENERATOR** Using **BG_RandGenerator()** method.</br>
![random_ranges](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/random_ranges.jpg?raw=true "")

**CLEAR-CONSOLE** Using **BG_ClearScreen()** method.</br>
![clear_screen](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/clear_screen.jpg?raw=true "")


# BoardGamr-Engine Logs and errors :

## Error/Exception Handling :

All the error/exception handling is done by engine itself like if you tried to enter invalid data in board,or adding wrong cards to deck or forgot to import any module from engine etc engine will throw error.So you don't have to check for any error by yourself.

![error_no_module](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/error_no_module.jpg?raw=true "")
![board_error](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/board_error.jpg?raw=true "")

## Methods Accessibility :

All **Public** and **Semi-Public** methods are accessible . But **Private** methods are not and library will throw error if you tried to access them.

![private_method_error](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/private_method_error.jpg?raw=true "")

## Engine Logs :

Logs are **disabled** by default but if you want engine to maintain logs use **BG_EnableLogs()** method to **enable** logs.
or if you want to **disable** logs again you can use **BG_DisableLogs()** method.

![enable_disable_logs](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/resources/enable_disable_logs.jpg?raw=true "")


**DOCUMENTATION INFO :** Go to **_docs_** folder and open **_index.html_** or click here **[BoardGamr-Docs](https://github.com/haseeb-heaven/BoardGamr-Engine/blob/master/docs)**


**VERSION INFO :**<br/>
BoardGamr-Engine Version : V 1.0  Dated : 17/02/2019.<br/>
