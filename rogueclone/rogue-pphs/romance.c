/*
 * Functions for dealing with problems of the heart
 *
 * @(#)romance.c	3.2 (Berkeley) 6/15/81
 *
 * Rogue: Exploring the Cavern of Cuties
 * Copyright (C) 1980, 1981 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#include "curses.h"
#include <ctype.h>
#include <string.h>
#include "rogue.h"

count_bits_set(v)
unsigned v; // count bits set in this (32-bit value)
{
    unsigned c = v - ((v >> 1) & 0x55555555);
    c = ((c >> 2) & 0x33333333) + (c & 0x33333333);
    c = ((c >> 4) + c) & 0x0F0F0F0F;
    c = ((c >> 8) + c) & 0x00FF00FF;
    c = ((c >> 16) + c) & 0x0000FFFF;
    return c;
}

/*
 * flirt:
 *	Make eyes in the given direction
 */

flirt(ydelta, xdelta)
int ydelta, xdelta;
{
    register struct linked_list *mob;
    struct object obj = {};

    obj.o_pos = hero;
    obj.o_type = '~';
    do_motion(&obj, ydelta, xdelta);
    mvwaddch(cw, hero.y, hero.x, PLAYER);
    if ((mob = find_mons(obj.o_pos.y, obj.o_pos.x)) == NULL)
    {
        const char *msgs[] = {
            "You wink at nothing in particular.",
            "You smile suggestively at the wall.",
            "Unprompted, you suddenly blush.",
        };
        msg(rndchoice(msgs));
    }
    else
    {
        register struct thing *tp = (struct thing *) ldata(mob);
        int attr = count_bits_set(tp->t_stats.s_ont ^ player.t_stats.s_ont);
        attr += tp->t_stats.s_int - 2;
        if (rnd(NUM_FEATURES) < attr)
        {
            tp->t_stats.s_int++;
            const char *msgs[] = {
                "The %s smiles back at you.",
                "You catch the %s staring at you out of the corner of eir eye.",
                "The %s blushes and waves cautiously.",
            };
            msg(rndchoice(msgs), killname(tp->t_type));
        }
        else if (attr <= 0)
        {
            tp->t_stats.s_int--;
            const char *msgs[] = {
                "The %s scowls at you.",
                "The %s tells you to stop it.",
                "The %s is sick of your crap.",
            };
            msg(rndchoice(msgs), killname(tp->t_type));
            wake_monster(tp->t_pos.y, tp->t_pos.x);
        }
        else
        {
            const char *msgs[] = {
                "The %s ignores you.",
                "The %s is completely uninterested in you.",
                "The %s acts like it can't hear you.",
                "The %s doesn't care.",
            };
            msg(rndchoice(msgs), killname(tp->t_type));
        }
    }
}

gift(ydelta, xdelta)
int ydelta, xdelta;
{
    register struct linked_list *obj, *nobj;
    register struct linked_list *mob;
    register struct object *op;
    register struct thing *tp;
    register int liking;

    if ((mob = find_mons(hero.y + ydelta, hero.x + xdelta)) == NULL)
    {
        msg("There's no-one around here.");
	return(0);
    }
    tp = (struct thing *) ldata(mob);

    if ((obj = get_item("give", 0)) == NULL)
        return;
    op = (struct object *) ldata(obj);
    if (!dropcheck(op))
	return;

    liking = count_bits_set(
        hash(op->o_type * op->o_which) & tp->t_stats.s_ont) - 1;
    if ((liking == 0 || liking == -1)
        || liking > 0 && tp->t_stats.s_int <= MAYBE_INTERESTED)
    {
        const char *msgs[] = {
            "The %s ignores %s",
            "The %s doesn't care for %s",
            "The %s isn't interested in %s",
        };
        msg(rndchoice(msgs), killname(tp->t_type), inv_name(op, TRUE));
        return;
    }    
    else if (liking > 0)
    {
        const char *msgs[] = {
            "The %s accepts %s.",
            "The %s smiles and takes %s.",
        };
        msg(rndchoice(msgs), killname(tp->t_type), inv_name(op, TRUE));
        tp->t_stats.s_int += liking * 10;
    }
    else
    {
        const char *msgs[] = {
            "The %s throws away %s.",
            "The %s breaks %s.",
            "The %s hates %s.",
        };
        msg(rndchoice(msgs), killname(tp->t_type), inv_name(op, TRUE));
        tp->t_stats.s_int -= liking * 2;
        wake_monster(tp->t_pos.y, tp->t_pos.x);
    }
    
    /*
     * Take it out of the pack
     */
    if (op->o_count >= 2 && op->o_type != WEAPON)
    {
	nobj = new_item(sizeof *op);
	op->o_count--;
	op = (struct object *) ldata(nobj);
	*op = *((struct object *) ldata(obj));
	op->o_count = 1;
	obj = nobj;
	if (op->o_group != 0)
		inpack++;
    }
    else
	detach(pack, obj);
    inpack--;
}

embrace()
{
    register struct thing *tp = NULL;
    register int liking;
    register int dx, dy;

    for (dx = -1; dx <= 1; ++dx)
    {
        for (dy = -1; dy <= 1; ++dy)
        {
            register struct linked_list *mob;
            if ((mob = find_mons(hero.y + dy, hero.x + dx)))
            {
                register struct thing *atp = (struct thing *)ldata(mob);
                if (!tp || atp->t_stats.s_int > tp->t_stats.s_int)
                    tp = atp;
            }
        }
    }


    if (tp == NULL)
    {
        msg("You wrap your arms around yourself.");
	return;
    }
    else if (tp->t_stats.s_int < READY)
    {
        if (tp->t_stats.s_int > 0)
            tp->t_stats.s_int /= 2;
        else
            tp->t_stats.s_int--;
        msg("The %s dodges out of the way.", killname(tp->t_type));
        return;
    }

    if (amulet)
    {
        total_winner(tp->t_type);
    }
    else
    {
        mostly_winner(tp->t_type);
    }
}
