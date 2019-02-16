#include "BG_Player.h"

/**
 * @description - Get random position for player or computer bot.
 * @return - On success it returns random position in range [0 to BOARD_SIZE] and On Error it return -1.
 */

uint BG_GetRandPosition(void)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called\n",BG_FUNC);
    }

    uint rand_pos = NUL;
    if(bg_board_size == NUL)
    {
        ShowError("%s -> ERROR : Use BG_InitGameBoard() method to initialize game board first!. Occurred at line no : %d\"\n",BG_FUNC,BG_LINE);
        rand_pos = BG_ERROR;
    }
    else
    {
        rand_pos = BG_RandGenerator(NUL,bg_board_size - 1);
    }
    SetPrivateAccess(TRUE);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rand_pos);
    }
    SetPrivateAccess(FALSE);
    return rand_pos;
}

/**
 * @description - Get random player turn  between 1 - 2 players.
  * @param -
 * turn_1 : Number designated with player_1's player_turn.
  * turn_2 : Number designated with player_2's player_turn.
 * @return - Returns random turn in range [Player_1 to Player_2].
 */

uint BG_GetRandTurn(int turn_1,int turn_n)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tturn_1 : %d\tturn_2 : %d\n",BG_FUNC,turn_1,turn_n);
    }

    uint rand_turn = BG_RandGenerator(turn_1,turn_n);
    SetPrivateAccess(TRUE);

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %u\n",BG_FUNC,rand_turn);
    }
    SetPrivateAccess(FALSE);
    return rand_turn;
}

/**
 * @description - Get player turn  between 2 - 4 players including player vs computer.
  * @param -
 * play_mode : Game playing mode use Enum PLAY_MODE to provide values.
  * n_players : Number  of players playing. [Required only in FRIEND_MODE].
  * roll_dice : Ask for roll dice input or not . Use TRUE or FALSE.
  * print_info : Whether to print information on rolled dice numbers or not . Use TRUE or FALSE.
 * @return - Returns turn number related with player_id. [See Enum PLAYER_ID for more information.]
 */

int BG_GetPlayerTurn(int play_mode,int n_players,bool roll_dice,bool print_info)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\tplay_mode : %d\tn_players : %d\troll_dice : %d\tprint_info : %s\n",BG_FUNC,play_mode,n_players,roll_dice,GetBoolAlpha(print_info));
    }

    int player_turn = 0,player_index = 1;
    int p1_dice = 0, p2_dice = 0, p3_dice = 0, p4_dice = 0,cmp_dice = 0,p_dice = 0;
    char roll_choice = '\0';

    /*Roll dice for selected players.*/
    switch(play_mode)
    {
    case COMPUTER_MODE :
        if(IsLogEnabled())
        {
            AddLog("%s -> COMPUTER_MODE selected\n",BG_FUNC);
        }

        if(roll_dice)
        {
            if(IsLogEnabled())
            {
                AddLog("%s -> Entered rolling dice section\n",BG_FUNC);
            }

            printf("\nRoll a dice to select who goes first!- Press 'R' key : ");

            while((roll_choice = getchar()) != '\n' && roll_choice != EOF); //fflush alternative.
            roll_choice = getchar();

            if(roll_choice == 'r' || roll_choice == 'R')
                p1_dice = BG_RollDie();

            SetPrivateAccess(TRUE);
            if(IsLogEnabled())
            {
                AddLog("%s -> Exiting rolling dice section\n",BG_FUNC);
            }
        }
        else
        {
            if(IsLogEnabled())
            {
                AddLog("%s -> Entering non-dice section\n",BG_FUNC);
            }
            p1_dice = BG_RollDie();
            cmp_dice = BG_RollDie();
            SetPrivateAccess(TRUE);
            if(IsLogEnabled())
            {
                AddLog("%s -> Exiting non-dice section\n",BG_FUNC);
            }
        }
        break;

    case FRIEND_MODE :
        if(IsLogEnabled())
        {
            AddLog("%s -> FRIEND_MODE selected\n",BG_FUNC);
        }

        do
        {
            if(roll_dice)
            {
                if(IsLogEnabled())
                {
                    AddLog("%s -> Entered rolling dice section\n",BG_FUNC);
                }

                printf("\nPlayer_%d Roll a dice to select who goes first!- Press 'R' key  : ",player_index);

                while((roll_choice = getchar()) != '\n' && roll_choice != EOF); //fflush alternative.
                roll_choice = getchar();

                if(roll_choice == 'r' || roll_choice == 'R')
                {
                    (player_index == PLAYER_1) ? (p1_dice = BG_RollDie()) : (player_index == PLAYER_2) ? (p2_dice = BG_RollDie()) : (player_index == PLAYER_3) ? (p3_dice = BG_RollDie()) : (p4_dice = BG_RollDie());
                }

                SetPrivateAccess(TRUE);
                if(IsLogEnabled())
                {
                    AddLog("%s -> Exiting rolling dice section\n",BG_FUNC);
                }
            }
            else
            {
                if(IsLogEnabled())
                {
                    AddLog("%s -> Entering non-dice section\n",BG_FUNC);
                }
                (player_index == PLAYER_1) ? (p1_dice = BG_RollDie()) : (player_index == PLAYER_2) ? (p2_dice = BG_RollDie()) : (player_index == PLAYER_3) ? (p3_dice = BG_RollDie()) : (p4_dice = BG_RollDie());

                SetPrivateAccess(TRUE);
                if(IsLogEnabled())
                {
                    AddLog("%s -> Exiting non-dice section\n",BG_FUNC);
                }
            }
        }
        while(player_index++ < n_players);
        break;
    }

    /*Select turn for 2-Players (Computer and Player_1).*/
    if(p2_dice == NUL && p3_dice == NUL && p4_dice == NUL)
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> 2-Players (Computer and Player_1) section selected\n",BG_FUNC);
        }
        player_turn = (cmp_dice  >=  p1_dice) ? PLAYER_COMP : PLAYER_1;
        if(print_info)
        {
            printf("\nPlayer rolled : %d\tComputer rolled : %d\n",p1_dice,cmp_dice);
        }
    }

    /*Select turn for 2-Players (Player_1 and Player_2).*/
    else if(p2_dice != NUL && p3_dice == NUL && p4_dice == NUL)
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> 2-Players (Player_1 and Player_2) section selected\n",BG_FUNC);
        }

        player_turn = (p1_dice  >=  p2_dice) ? PLAYER_1 : PLAYER_2;
        if(print_info)
        {
            printf("\nPlayer_1 rolled : %d\tPlayer_2 rolled : %d\n",p1_dice,p2_dice);
        }
    }

    /*Select turn for 3-Players.*/
    else if(p2_dice != NUL && p3_dice != NUL && p4_dice == NUL)
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> 3-Players section selected\n",BG_FUNC);
        }

        player_turn = p1_dice  >=  p2_dice ? (p1_dice  >=  p3_dice ? PLAYER_1 : PLAYER_3) : (p2_dice  >=  p3_dice ? PLAYER_2 : PLAYER_3) ;
        if(print_info)
        {
            printf("\nPlayer_1 rolled : %d\tPlayer_2 rolled : %d\tPlayer_3 rolled : %d\n",p1_dice,p2_dice,p3_dice);
        }
    }

    /*Select turn for 4-Players.*/
    else if(p2_dice != NUL && p3_dice != NUL && p4_dice != NUL)
    {
        if(IsLogEnabled())
        {
            AddLog("%s -> 4-Players section selected\n",BG_FUNC);
        }

        player_turn =  (p1_dice >= p2_dice && p1_dice >= p3_dice && p1_dice >= p4_dice) ? PLAYER_1 :  (p2_dice >= p1_dice && p2_dice >= p3_dice && p2_dice >= p4_dice) ? PLAYER_2 : (p3_dice >= p1_dice && p3_dice >= p2_dice && p3_dice >= p4_dice) ? PLAYER_3 : (p4_dice >= p1_dice && p4_dice >= p2_dice && p4_dice >= p3_dice) ? PLAYER_4 : BG_ERROR;
        if(print_info)
        {
            printf("\nPlayer_1 rolled : %d\tPlayer_2 rolled : %d\tPlayer_3 rolled : %d\tPlayer_4 rolled : %d\n",p1_dice,p2_dice,p3_dice,p4_dice);
        }
    }

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %d\n",BG_FUNC,player_turn);
    }
    SetPrivateAccess(FALSE);
    return player_turn;
}

/**
 * @description - Get total score in percentage.
  * @param - total_score : Total score of player.
  * total_games : Total games played by player.
 * @return - Returns score percentage in float format.
 */

float BG_GetScorePercent(int total_score,int total_games)
{
    SetPrivateAccess(TRUE);
    if(IsLogEnabled())
    {
        AddLog("%s -> called with arguments\ttotal_score : %d\ttotal_games : %d\n",BG_FUNC,total_score,total_games);
    }

    float score_percent = ( ((float)total_score) / ((float)total_games)  ) * 100;

    if(IsLogEnabled())
    {
        AddLog("%s -> ended successfully with return value : %f\n",BG_FUNC,score_percent);
    }
    SetPrivateAccess(FALSE);
    return score_percent;
}
