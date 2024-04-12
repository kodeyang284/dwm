/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=15:antialias=true:autohint=true" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#fcfbf4";
static const char col_gray4[]       = "#eeeeee";
static const char col_borderSel[]   = "#005577";
static const char col_bgSel[]       = "#444444";
static const unsigned int baralpha = 0x30;
static const unsigned int baralselpha = 0x90;
static const unsigned int borderalpha = 0xb0;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_bgSel, col_borderSel },
};
static const unsigned int alphas[][3] = {
 	/*               fg      bg           border*/
  [SchemeNorm] = { OPAQUE, baralpha,    borderalpha },
  [SchemeSel]  = { OPAQUE, baralselpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "󰈹", "󰎪", "󰬽", "󰲨", "󰬿", "󰎶", "󰭁", "💤" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance       title           tags mask   iscentered   isfloating   monitor   borderwidth   float x,y,w,h       scratch key*/
	{ NULL,          NULL,          NULL,           0,          1,           0,           -1,       -1,           -1,-1,-1,-1,        0  },
	{ "firefox",     NULL,          NULL,           1 << 1,     1,           0,           -1,       -1,           -1,-1,-1,-1,        0  },
	{ NULL,          "qq",          NULL,           1 << 8,     1,           1,           -1,       -1,           -1,-1,-1,-1,        0  },
	{ NULL,    "telegram-desktop",  NULL,           1 << 8,     1,           1,           -1,       -1,           -1,-1,-1,-1,        0  },
	{ "floatterm",   NULL,          NULL,           0,          1,           1,           -1,       -1,           -1,-1,-1,-1,        0  },
	{ "scratchapp",  NULL,          NULL,           0,          0,           1,           -1,       6,            1800,-1,800,600,    0  },
	{ "scratchpad",  "scratchpad",  "scratchpad",   0,          1,           1,           -1,       -1,           -1,-1,-1,-1,       's' },
	{ "builtinapp",  NULL,          "musicfox",     0,          0,           1,           -1,       6,            2000,-1,500,600,   'm' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
  { "󰛾",      monocle },
	{ "",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define SUPER Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define __TERMINAL  "alacritty", "msg", "create-window"
#define BUILTINAPP(o, name, cmd) {o, __TERMINAL, "--class", "builtinapp", \
                                  "-o", "font.size=6.5", "-T", name, \
                                  "-e", cmd, NULL }


/* commands */
static const char *dmenucmd[]      = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]       = { __TERMINAL, NULL };
static const char *termfloat[]     = { __TERMINAL, "--class", "floatterm", NULL };


/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", __TERMINAL, "--class", "scratchpad", "-T", "scratchpad", "-o", "font.size=6.5", NULL };
static const char *musicfoxcmd[]   = BUILTINAPP("m", "musicfox", "musicfox");

static const char ** const startup_programs[] = { NULL };
    
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = termfloat } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_e,      togglescratch,  {.v = musicfoxcmd } },
	{ SUPER,                        XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY|ShiftMask,             XK_b,      toggleborder,   {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ SUPER,                        XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_l,      shiftview,      {.i = +1 } },
	{ SUPER,                        XK_h,      setmfact,       {.f = -0.05} },
	{ SUPER,                        XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscreen, {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 
  /* shell function key bindings */
	{ 0,          XF86XK_AudioLowerVolume,     spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -1000") },
	{ 0,          XF86XK_AudioRaiseVolume,     spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +1000") },
	{ 0,          XF86XK_AudioMute,            spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ 0,          XF86XK_MonBrightnessUp,      spawn,          SHCMD("light -A 5") },
	{ 0,          XF86XK_MonBrightnessDown,    spawn,          SHCMD("light -U 5") },
  { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("togglemon") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("alacritty") },
	{ MODKEY,                       XK_o,      spawn,          SHCMD("dentry") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("pkill -x picom") },
	{ MODKEY,              XK_bracketleft,     spawn,          SHCMD("dwmapps") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
