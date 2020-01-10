/* mdump.c -- Dump text image				-*- coding: euc-jp; -*-
   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012
     National Institute of Advanced Industrial Science and Technology (AIST)
     Registration Number H15PRO112

   This file is part of the m17n library.

   The m17n library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   The m17n library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the m17n library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   02111-1307, USA.  */

/***en
    @enpage m17n-dump dump text image

    @section m17n-dump-synopsis SYNOPSIS

    m17n-dump [ OPTION ... ] [ FILE ]

    @section m17n-dump-description DESCRIPTION

    Dump a text as PNG image file.

    The PNG file is written to a file created in the current directory
    with the name "BASE.png" where BASE is the basename of FILE.  If
    FILE is omitted, text is read from standard input, and the image
    is dumped into the file "output.png".

    The following OPTIONs are available.

    <ul>

    <li> -s SIZE

    SIZE is the font size in point.  The default font size is 12 point.

    <li> -d DPI

    DPI is the resolution in dots per inch.  The default resolution is
    300 dpi.

    <li> -p PAPER

    PAPER is the paper size: a4, a4r, a5, a5r, b5, b5r, letter, WxH,
    or W.  In the case of WxH, W and H are the width and height in
    millimeter.  In the case of W, W is the width in millimeter.  If
    this option is specified, PAPER limits the image size.  If FILE is
    too large for a single page, multiple files with the names
    "BASE.01.png", "BASE.02.png", etc. are created.

    <li> -m MARGIN

    MARGIN is the horizontal and vertical margin in millimeter.  The
    default margin is 20 mm.  It is ignored when PAPER is not
    specified.

    <li> -c POS

    POS is the character position of cursor to draw.  By default,
    cursor is not drawn.

    <li> -x

    FILE is assumed to be an XML file generated by the serialize
    facility of the m17n library, and FILE is deserialized before an
    image is created.

    <li> -w

    Each line is broken at word boundary.

    <li> -f FILTER

    FILTER is a string containing a shell command line.  If this
    option is specified, the PNG image is not written info a
    file but is given to FILTER as standard input.  If FILTER
    contains "%s", that part is replaced by a basename of FILE.
    So, the default behaviour is the same as specifying "cat >
    %s.png" as FILTER.

    If FILTER is just "-", the PNG image is written to stdout.

    <li> -a

    Enable anti-alias drawing.

    <li> --family FAMILY

    Prefer a font whose family name is FAMILY.

    <li> --language LANG

    Prefer a font specified for the language LANG.  LANG must be a
    2-letter code of ISO 630 (e.g. "en" for English).

    <li> -fg FOREGROUND

    Specify the text color.  The supported color names are those of
    HTML 4.0 and "#RRGGBB" notation.

    <li> -bg BACKGROUND

    Specify the background color.  The supported color names are the
    same as FOREGROUND, except that if "transparent" is specified,
    make the background transparent.

    <li> -r

    Specify that the orientation of the text is right-to-left.

    <li> -q

    Quiet mode.  Don't print any messages.

    <li> --version

    Print the version number.

    <li> -h, --help

    Print this message.

    </ul>
*/
/***ja
    @japage m17n-dump テキスト画像のダンプ

    @section m17n-dump-synopsis SYNOPSIS

    m17n-dump [ OPTION ... ] [ FILE ]

    @section m17n-dump-description DESCRIPTION

    テキストを PNG 画像としてダンプする。 

    PNG 画像は現在のディレクトリに作られた "BASE.png" という名前の 
    ファイルに書き込まれる。ここで BASE はFILE の basename である。 
    FILE が省略されれば、テキストは標準入力から読まれ、画像は 
    "output.png" にダンプされる。

    以下のオプションが利用できる。

    <ul>

    <li> -s SIZE

    SIZE はフォントの大きさをポイント単位で示したものである。デフォル
    トの大きさは 12 ポイント。

    <li> -d DPI

    DPI は解像度を１インチあたりのドット単位で示したものである。デフォ 
    ルトの解像度は 300 dpi。

    <li> -p PAPER

    PAPER はぺーパサイズ : a4, a4r, a5, a5r, b5, b5r, letter, WxH また
    は W。 WxH の場合、 W と H は幅と高さをミリメータ単位で示したもの。
    W の場合、 W は幅をミリメータ単位で示したもの。このオプションが指定
    されている場合は、 PAPER が画像サイズを制限す る。FILE が 1 ページ
    に納まらないほど大きい場合は、"BASE.01.png", "BASE.02.png" 等の名前
    のついた複数のファイルが作られる。

    <li> -m MARGIN

    MARGIN は水平、垂直マージンをミリメータ単位で示したものである。デ 
    フォルトのマージンは 20 mm。PAPER が指定されていなければ無視される。

    <li> -c POS

    POS はカーソルの文字位置。デフォルトでは、カーソルは描かれない。

    <li> -x

    FILE は m17n ライブラリのシリアライズ機能によって作られた XML ファ 
    イルであり、画像を生成する前にデシリアライズされる。

    <li> -w

    語の境界で改行する。 

    <li> -f FILTER

    FILTER はシェルコマンド行を含む文字列である。このオプションが指定
    されていれば、PNG 画像はファイルに書かれるのではなく、FILTER に 
    標準入力として渡される。 FILTER が "%s" を含んでいれば、それは FILE 
    のベースネームに置き換えられる。このプログラムのデフォルトの振舞い
    と、FILTER に "cat > %s.png" を指定した場合の振舞は同一である。

    もし FILTER が単に "-" であれば、 PNG 画像は stdout に出力される。

    <li> -a

    アンチエイリアス処理を行う。

    <li> --family FAMILY

    ファミリィ名が FAMILY のフォントを優先的に使う。

    <li> --language LANG

    言語 LANG 用に指定されたフォントを優先的に使う。LANG は ISO 630 の
    ２文字コード（例：英語は "en" ）でなければならない。

    <li> -fg FOREGROUND

    テキストの色を指定する。HTML 4.0 の色の名前および "#RRGGBB" 記法を
    サポート。

    <li> -bg BACKGROUND

    背景の色を指定する。サポートされている色の名前は FOREGROUND 同じ。
    ただし、もし "transparent" が指定されたら背景を透明にする。

    <li> -r

    Specify that the orientation of the text is right-to-left.

    <li> -q

    一切のメッセージを表示しない。 

    <li> --version

    バージョン番号を表示する。

    <li> -h, --help

    このメッセージを表示する。 

    </ul>
*/

#ifndef FOR_DOXYGEN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>

#if defined (HAVE_FREETYPE) && defined (HAVE_GD)
#include <gd.h>

#include <m17n-gui.h>
#include <m17n-misc.h>

/* Enumuration of the supported paper types.  */
enum paper_type
  {
    PAPER_A4,
    PAPER_A4R,
    PAPER_A5,
    PAPER_A5R,
    PAPER_B5,
    PAPER_B5R,
    PAPER_LETTER,
    PAPER_USER,
    PAPER_NOLIMIT
  };

/* Array of paper sizes for the supported paper types.  */
struct
{
  int width, height;		/* in millimeter */
} paper_size[PAPER_NOLIMIT] = {
  { 210, 297 },			/* a4 */
  { 297, 210 },			/* a4r */
  { 148, 210 },			/* a5 */
  { 210, 148 },			/* a5r */
  { 250, 176 },			/* b5 */
  { 176, 250 },			/* b5r */
  { 216, 279 },			/* letter */
};


/* Print the usage of this program (the name is PROG), and exit with
   EXIT_CODE.  */

void
help_exit (char *prog, int exit_code)
{
  char *p = prog;

  while (*p)
    if (*p++ == '/')
      prog = p;

  printf ("Usage: %s [ OPTION ...] [ FILE ]\n", prog);
  printf ("Dump a text as a PNG image into a file.\n");
  printf ("  The PNG file is created in the current directory\n");
  printf ("    with the name \"BASE.png\" where BASE is the basename of FILE.\n");
  printf ("  If FILE is omitted, text is read from standard input, and\n");
  printf ("    dumped into the file \"output.png\".\n");
  printf ("The following OPTIONs are available.\n");
  printf ("  %-13s %s", "-s SIZE",
	  "Font size in 1/10 point (default 120).\n");
  printf ("  %-13s %s", "-d DPI",
	  "Resolution in dots per inch (defualt 300).\n");
  printf ("  %-13s %s", "-p PAPER",
	  "Paper size; a4, a4r, a5, a5r, b5, b5r, letter, W, or WxH.\n");
  printf ("  %-13s %s", "-m MARGIN",
	  "Marginal space in millimeter (default 20).\n");
  printf ("  %-13s %s", "-c POS",
	  "Character position of cursor to draw (default no cursor)\n");
  printf ("  %-13s %s", "-x",
	  "FILE is assumed to be an XML file.\n");
  printf ("  %-13s %s", "-f FILTER",
	  "String containing a shell command line to be used as a filter.\n");
  printf ("  %-13s %s", "-w", "Each line is broken at word boundary.\n");
  printf ("  %-13s %s", "-a", "Enable anti-alias drawing.\n");
  printf ("  %-13s %s", "--family FAMILY", 
	  "Prefer a font whose family is FAMILY.\n");
  printf ("  %-13s %s", "--language LANG", 
	  "Prefer a font specified for the langauge LANG.\n");
  printf ("  %-13s %s", "-r", 
	  "Specify that the orientation of the text is right-to-left.\n");
  printf ("  %-13s %s", "-fg FOREGROUND",
	  "Specify the text color (HTML 4.0 color names or \"#RRGGBB\").\n");
  printf ("  %-13s %s", "-bg BACKGROUND",
	  "Specify the background color (\"transparent\" for transparent)\n");
  printf ("  %-13s %s", "-q", "Quiet mode.  Don't print any messages.\n");
  printf ("  %-13s %s", "--version", "Print the version number.\n");
  printf ("  %-13s %s", "-h, --help", "Print this message.\n");
  exit (exit_code);
}


/* Format MSG by FMT and print the result to the stderr, and exit.  */

#define FATAL_ERROR(fmt, arg)	\
  do {				\
    fprintf (stderr, fmt, arg);	\
    exit (1);			\
  } while (0)


/* Move POS to the next line head in M-text MT whose length is LEN.
   If POS is already on the last line, set POS to LEN.  */

#define NEXTLINE(pos, len)			\
  do {						\
    pos = mtext_character (mt, pos, len, '\n');	\
    if (pos < 0)				\
      pos = len;				\
    else					\
      pos++;					\
  } while (0)


/* Find the range of M-text MT that fits in one page of height HEIGHT
   when drawn from the character position POS.  Set RECT->y to the
   Y-offset of the first baseline.  */

int
find_page_end (MFrame *frame, int height, MText *mt, int pos,
	       MDrawControl *control, MDrawMetric *rect)
{
  int len = mtext_len (mt);
  int to = pos;
  int y = 0, yoff;

  while (to < len)
    {
      int next = to;

      NEXTLINE (next, len);
      mdraw_text_extents (frame, mt, to, next, control, NULL, NULL, rect);
      if (to == pos)
	yoff = rect->y;
      if (y + rect->height > height)
	{
	  MDrawGlyphInfo info;

	  while (to < next)
	    {
	      mdraw_glyph_info (frame, mt, to, to, control, &info);
	      if (y + info.metrics.height > height)
		break;
	      y += info.metrics.height;
	      to = info.line_to;
	    }
	  break;
	}
      y += rect->height;
      to = next;
    }

  rect->y = yoff;
  return to;
}

/* Dump the image in IMAGE into a file whose name is generated from
   FILENAME and PAGE_INDEX (if it is not zero).  */

void
dump_image (gdImagePtr image, char *filename, char *filter,
	    int page_index, int quiet_mode)
{
  FILE *fp;

  if (page_index)
    {
      char *name = alloca (strlen (filename) + 8);

      sprintf (name, "%s.%02d", filename, page_index);
      filename = name;
    }

  if (filter)
    {
      if (filter[0] == '-' && filter[1] == '\0')
	fp = stdout;
      else
	{
	  char *command = alloca (strlen (filename) + strlen (filter) + 1);

	  sprintf (command, filter, filename);
	  fp = popen (command, "w");
	  if (! fp)
	    FATAL_ERROR ("Can't run the command \"%s\"\n", command);
	  if (! quiet_mode)
	    printf ("Running \"%s\" ... ", command);
	}
    }
  else
    {
      char *fullname = alloca (strlen (filename) + 5);

      sprintf (fullname, "%s.png", filename);
      fp = fopen (fullname, "w");
      if (! fp)
	FATAL_ERROR ("Can't write to \"%s\"\n", fullname);
      if (! quiet_mode)
	printf ("Writing %s ... ", fullname);
    }

  /* Generate PNG.  */
  gdImagePng (image, fp);
  if (fp != stderr)
    fclose (fp);
  if (! quiet_mode)
    printf (" done (%dx%d)\n", image->sx, image->sy);
}

extern int line_break (MText *mt, int pos, int from, int to, int line, int y);

int
main (int argc, char **argv)
{
  int fontsize = 120;
  int paper = PAPER_NOLIMIT;
  int dpi = 300;
  int margin = 20;
  int xml = 0;
  FILE *fp = stdin;
  int cursor_pos = -1;
  int quiet_mode = 0;
  int break_by_word = 0;
  char *filter = NULL;
  int paper_width, paper_height;
  int anti_alias = 0;
  char *family_name = NULL;
  char *lang_name = NULL;
  char *fg_color = NULL, *bg_color = NULL;
  int transparent = 0;
  int r2l = 0;
  int i;
  int page_index;
  gdImagePtr image;
  int bg_rgb;

  MFrame *frame;
  MText *mt;
  MDrawControl control;
  MDrawMetric rect;
  char *filename = "output";
  int len, from;
  char *fontset_name = "generic";


  /* Parse the command line arguments.  */
  for (i = 1; i < argc; i++)
    {
      if (! strcmp (argv[i], "--help")
	       || ! strcmp (argv[i], "-h")
	       || ! strcmp (argv[i], "-?"))
	help_exit (argv[0], 0);
      else if (! strcmp (argv[i], "--version"))
	{
	  printf ("m17n-dump (m17n library) %s\n", M17NLIB_VERSION_NAME);
	  printf ("Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012 AIST, JAPAN\n");
	  exit (0);
	}
      else if (! strcmp (argv[i], "-s") && i + 1< argc)
	{
	  fontsize = atoi (argv[++i]);
	  if (! fontsize)
	    FATAL_ERROR ("Invalid font size: %s\n", argv[i]);
	}
      else if (! strcmp (argv[i], "-p") && i + 1< argc)
	{
	  int w, h;

	  i++;
	  if (! strcmp (argv[i], "a4"))
	    paper = PAPER_A4;
	  else if (! strcmp (argv[i], "a4r"))
	    paper = PAPER_A4R;
	  else if (! strcmp (argv[i], "a5"))
	    paper = PAPER_A5;
	  else if (! strcmp (argv[i], "a5r"))
	    paper = PAPER_A5R;
	  else if (! strcmp (argv[i], "b5"))
	    paper = PAPER_B5;
	  else if (! strcmp (argv[i], "b5r"))
	    paper = PAPER_B5R;
	  else if (! strcmp (argv[i], "letter"))
	    paper = PAPER_LETTER;
	  else if (sscanf (argv[i], "%dx%d", &w, &h) == 2
		   && w > 0 && h > 0)
	    {
	      paper = PAPER_USER;
	      paper_size[paper].width = w;
	      paper_size[paper].height = h;
	    }
	  else if (sscanf (argv[i], "%d", &w) == 1
		   && w > 0)
	    {
	      paper = PAPER_USER;
	      paper_size[paper].width = w;
	      paper_size[paper].height = 0;
	    }
	  else
	    FATAL_ERROR ("Invalid paper type: %s\n", argv[i]);
	}
      else if (! strcmp (argv[i], "-d") && i + 1< argc)
	{
	  dpi = atoi (argv[++i]);
	  if (! dpi)
	    FATAL_ERROR ("Invalid resolution: %s\n", argv[i]);
	}
      else if (! strcmp (argv[i], "-m") && i + 1< argc)
	{
	  margin = atoi (argv[++i]);
	  if (margin < 0)
	    FATAL_ERROR ("Invalid margin: %s\n", argv[i]);
	}
      else if (! strcmp (argv[i], "-c") && i + 1< argc)
	{
	  cursor_pos = atoi (argv[++i]);
	  if (cursor_pos < 0)
	    FATAL_ERROR ("Invalid cursor position: %s\n", argv[i]);
	}
      else if (! strcmp (argv[i], "-f") && i + 1< argc)
	{
	  filter = argv[++i];
	}
      else if (! strcmp (argv[i], "-x"))
	{
	  xml = 1;
	}
      else if (! strcmp (argv[i], "-w"))
	{
	  break_by_word = 1;
	}
      else if (! strcmp (argv[i], "-q"))
	{
	  quiet_mode = 1;
	}
      else if (! strcmp (argv[i], "-a"))
	{
	  anti_alias = 1;
	}
      else if (! strcmp (argv[i], "--family"))
	{
	  family_name = argv[++i];
	}
      else if (! strcmp (argv[i], "--language"))
	{
	  lang_name = argv[++i];
	}
      else if (! strcmp (argv[i], "-r"))
	{
	  r2l = 1;
	}
      else if (argv[i][0] != '-')
	{
	  fp = fopen (argv[i], "r");
	  if (! fp)
	    FATAL_ERROR ("Fail to open the file %s!\n", argv[i]);
	  filename = basename (argv[i]);
	}
      else if (! strcmp (argv[i], "--fontset"))
	{
	  fontset_name = argv[++i];
	}
      else if (! strcmp (argv[i], "-fg"))
	{
	  if (i + 1 == argc)
	    {
	      fprintf (stderr, "Foreground color not specified\n");
	      help_exit (argv[0], 1);
	    }
	  fg_color = argv[++i];
	}
      else if (! strcmp (argv[i], "-bg"))
	{
	  if (i + 1 == argc)
	    {
	      fprintf (stderr, "Background color not specified\n");
	      help_exit (argv[0], 1);
	    }
	  i++;
	  if (! strcmp (argv[i], "transparent"))
	    transparent = 1;
	  else
	    bg_color = argv[i];
	}
      else
	{
	  fprintf (stderr, "Unknown or invalid option: %s\n", argv[i]);
	  help_exit (argv[0], 1);
	}
    }

  /* Initialize the m17n library.  */
  M17N_INIT ();
  if (merror_code != MERROR_NONE)
    FATAL_ERROR ("%s\n", "Fail to initialize the m17n library.");

  mt = mconv_decode_stream (Mcoding_utf_8, fp);
  fclose (fp);
  if (xml)
    mt = mtext_deserialize (mt);
  if (! mt)
    FATAL_ERROR ("%s\n", "Fail to decode the input file or stream!");

  len = mtext_len (mt);
  if (lang_name)
    mtext_put_prop (mt, 0, len, Mlanguage, msymbol (lang_name));

  if (paper == PAPER_NOLIMIT)
    paper_width = paper_height = margin = 0;
  else
    {
      paper_width = paper_size[paper].width * dpi / 25.4;
      paper_height = paper_size[paper].height * dpi / 25.4;
      margin = margin * dpi / 25.4;
    }

  {
    MPlist *plist = mplist (), *p;
    MFontset *fontset = mfontset (fontset_name);
    MFace *face = mface ();

    mface_put_prop (face, Mfontset, fontset);
    mface_put_prop (face, Msize, (void *) (fontsize * dpi / 100));
    if (family_name)
      {
	char *p;

	for (p = family_name; *p; p++)
	  if (isupper (*p)) *p = tolower (*p);
	mface_put_prop (face, Mfamily, msymbol (family_name));
      }
    if (fg_color)
      mface_put_prop (face, Mforeground, msymbol (fg_color));
    if (bg_color)
      mface_put_prop (face, Mbackground, msymbol (bg_color));
    p = mplist_add (plist, Mdevice, msymbol ("gd"));
    p = mplist_add (p, Mface, face);
    m17n_object_unref (face);
    frame = mframe (plist);
    m17n_object_unref (plist);
    if (! frame)
      FATAL_ERROR ("%s\n", "Can't open a frame (perhaps no font available)!");
  }

  memset (&control, 0, sizeof control);
  control.two_dimensional = 1;
  control.enable_bidi = 1;
  control.anti_alias = anti_alias;
  control.orientation_reversed = r2l;
  if (cursor_pos >= 0)
    {
      control.with_cursor = 1;
      if (cursor_pos > len)
	cursor_pos = len;
      control.cursor_pos = cursor_pos;
      control.cursor_width = -1;
    }
  else
    control.ignore_formatting_char = 1;
  if (break_by_word)
    control.line_break = mdraw_default_line_break;

  if (paper == PAPER_NOLIMIT)
    {
      control.max_line_width = 0;
      mdraw_text_extents (frame, mt, 0, len, &control, NULL, NULL, &rect);
      paper_width = rect.width;
      paper_height = rect.height;
    }
  else
    {
      control.max_line_width = paper_width - margin * 2;
      if (paper_height == 0)
	{
	  mdraw_text_extents (frame, mt, 0, len, &control, NULL, NULL, &rect);
	  paper_height = rect.height + margin * 2;
	}
    }

#if HAVE_GD > 1
  image = gdImageCreateTrueColor (paper_width, paper_height);
#else
  image = gdImageCreate (paper_width, paper_height);
#endif
  from = 0;
  page_index = 1;

  if (transparent)
    {
      MFace *face = mframe_get_prop (frame, Mface);
      MSymbol fg = mface_get_prop (face, Mforeground);
      int rgb_value = 0;

      if (fg)
	rgb_value = (int) msymbol_get (fg, msymbol ("  rgb"));
      if (rgb_value == 0xFFFFFF)
	bg_rgb = gdImageColorAllocate (image, 0, 0, 0);
      else
	bg_rgb = gdImageColorAllocate (image, 255, 255, 255);
      gdImageColorTransparent (image, bg_rgb);
#if HAVE_GD > 1
      gdImageAlphaBlending (image, 0);
#endif
    }
  else
    {
      MFace *face = mframe_get_prop (frame, Mface);
      MSymbol bg = mface_get_prop (face, Mbackground);
      if (bg)
	{
	  int rgb_value = (int) msymbol_get (bg, msymbol ("  rgb"));
	  bg_rgb = gdImageColorAllocate (image, rgb_value >> 16, 
					 (rgb_value >> 8) & 255, 
					 rgb_value & 255);
	}
      else
	bg_rgb = gdImageColorAllocate (image, 255, 255, 255);
    }

  while (from < len)
    {
      int to;

      if (paper == PAPER_NOLIMIT || paper_size[paper].height == 0)
	to = len;
      else
	to = find_page_end (frame, paper_height - margin * 2, mt, from,
			    &control, &rect);

      gdImageFilledRectangle (image, 0, 0, paper_width - 1, paper_height - 1,
			      bg_rgb);
      if (! r2l)
	mdraw_text_with_control (frame, image,
				 margin, margin - rect.y,
				 mt, from, to, &control);
      else
	mdraw_text_with_control (frame, image,
				 paper_width - margin, margin - rect.y,
				 mt, from, to, &control);
      dump_image (image, filename, filter,
		  ((from > 0 || to < len) ? page_index : 0),
		  quiet_mode);

      from = to;
      page_index++;
    }

  m17n_object_unref (frame);
  m17n_object_unref (mt);
  M17N_FINI ();
  gdImageDestroy (image);
  exit (0);
}

#else  /* not HAVE_FREETYPE nor HAVE_GD */

int
main (int argc, char **argv)
{
  fprintf (stderr, "Can't run without Freetype and GD library!\n");
  exit (1);
}

#endif  /* not HAVE_FREETYPE nor HAVE_GD */
#endif /* not FOR_DOXYGEN */
