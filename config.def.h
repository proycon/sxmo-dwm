/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
  "monospace:size=15", /* PP default start index */
  "monospace:size=11", /* PB default start index */
};
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "st",       NULL,       NULL,       0,            0,           1,         1,        -1,  0},
	{ "svkbd",    NULL,       NULL,       TAGMASK,      1,           1,         0,        -1,  1}, 
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|_|",      bstack },
	{ "[ ]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{0, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{0, MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{0, MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{0, MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
  /* PP */
	{1,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_appmenu.sh") },
	{2,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_appmenu.sh sys") },
	{3,  0,  XF86XK_AudioRaiseVolume, spawn, SHCMD("sxmo_screenlock") },
	{1,  0,  XF86XK_AudioLowerVolume, cyclelayout , {.i = +1 } },
	{2,  0,  XF86XK_AudioLowerVolume, rotatestack, {.i = +1} },
	{3,  0,  XF86XK_AudioLowerVolume, killclient, {0} },
	{1,  0,  XF86XK_PowerOff, spawn, SHCMD("pkill -9 svkbd-sxmo || svkbd-sxmo") },
	{2,  0,  XF86XK_PowerOff, spawn, SHCMD("sxmo_blinkled.sh green & $TERM") },
	{3,  0,  XF86XK_PowerOff, spawn, SHCMD("sxmo_blinkled.sh green & $BROWSER") },

	/* Used by scripts via xdotool */
	{0,  MODKEY|ShiftMask,  XK_e, shiftview, {.i = -1} },
	{0,  MODKEY|ShiftMask,  XK_r, shiftview, {.i = +1} },
	{0,  MODKEY,  XK_e, clienttagpush, {.i = -1} },
	{0,  MODKEY,  XK_r, clienttagpush, {.i = +1} },

	/* PBP */
	{ 0, MODKEY,                    XK_p,      spawn,          {.v = dmenucmd } },
	{ 0, MODKEY|ShiftMask,          XK_Return, spawn,          SHCMD("st") },
	{ 0, MODKEY,                    XK_b,      togglebar,      {0} },
	{ 0, MODKEY,                    XK_j,      focusstack,     {.i = +1 } },
	{ 0, MODKEY,                    XK_k,      focusstack,     {.i = -1 } },
	{ 0, MODKEY,                    XK_i,      incnmaster,     {.i = +1 } },
	{ 0, MODKEY,                    XK_o,      incnmaster,     {.i = -1 } },
	{ 0, MODKEY,                    XK_h,      setmfact,       {.f = -0.05} },
	{ 0, MODKEY,                    XK_l,      setmfact,       {.f = +0.05} },
	{ 0, MODKEY,                    XK_Return, zoom,           {0} },
	{ 0, MODKEY,                    XK_Tab,    view,           {0} },
	{ 0, MODKEY|ShiftMask,          XK_c,      killclient,     {0} },
	{ 0, MODKEY,                    XK_t,      setlayout,      {.v = &layouts[0]} },
	{ 0, MODKEY,                    XK_f,      setlayout,      {.v = &layouts[1]} },
	{ 0, MODKEY,                    XK_m,      setlayout,      {.v = &layouts[2]} },
	{ 0, MODKEY,                    XK_space,  setlayout,      {0} },
	{ 0, MODKEY|ShiftMask,          XK_space,  togglefloating, {0} },
	{ 0, MODKEY,                    XK_0,      view,           {.ui = ~0 } },
	{ 0, MODKEY|ShiftMask,          XK_0,      tag,            {.ui = ~0 } },
	{ 0, MODKEY,                    XK_comma,  focusmon,       {.i = -1 } },
	{ 0, MODKEY,                    XK_period, focusmon,       {.i = +1 } },
	{ 0, MODKEY|ShiftMask,          XK_comma,  tagmon,         {.i = -1 } },
	{ 0, MODKEY|ShiftMask,          XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1} },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("sxmo_appmenu.sh control") },
};

