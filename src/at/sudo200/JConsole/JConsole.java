package at.sudo200.JConsole;

import cz.adamh.utils.NativeUtils;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Library for fancy terminal formatting.
 * Ported from <a href="https://github.com/OE3KUW/console-htlstp">C</a> using <a href="https://en.wikipedia.org/wiki/Java_Native_Interface">JNI</a>.
 *
 * @author sudo200
 */
public class JConsole {
    public static final int BLACK = 0;
    public static final int RED = 1;
    public static final int GREEN = 2;
    public static final int YELLOW = 3;
    public static final int BLUE = 4;
    public static final int MAGENTA = 5;
    public static final int CYAN = 6;
    public static final int WHITE = 7;
    public static final int GRAY = 8;
    public static final int H_RED = 9;
    public static final int H_GREEN = 10;
    public static final int H_YELLOW = 11;
    public static final int H_BLUE = 12;
    public static final int H_MAGENTA = 13;
    public static final int H_CYAN = 14;
    public static final int H_WHITE = 15;

    public static final int C_INVISABLE = 0;
    public static final int C_SMALL = 1;
    public static final int C_MEDIUM = 16;
    public static final int C_LARGE = 1024;

    static {
        try {
            System.out.println();
            NativeUtils.loadLibraryFromJar("/at/sudo200/JConsole/lib/jconsole.dll");
        } catch (FileNotFoundException e) {
            throw new UnsatisfiedLinkError("Natives not found! Aborting...");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private JConsole() {
    }

    /**
     * Initialises console.
     * ALWAYS CALL BEFORE USING ANY OTHER METHOD!
     *
     * @author sudo200
     * @see JConsole#closeConsole()
     */
    public static native void initConsole();

    /**
     * Moves the cursor to the specified position.
     *
     * @param x X-Coordinate to move to. Starts at zero.
     * @param y Y-Coordinate to move to. Starts at zero.
     * @author sudo200
     */
    public static native void gotoxy(int x, int y);

    /**
     * Changes the text color.
     *
     * @param c Value from 0 to 15.
     * @author sudo200
     * @see JConsole
     */
    public static native void textcolor(int c);

    /**
     * Changes the background color.
     * Hint: For best results, use in combination with <code>clrscr()</code>
     *
     * @param c Value from 0 to 7.
     * @author sudo200
     * @see JConsole#clrscr()
     * @see JConsole
     */
    public static native void textbackground(int c);

    /**
     * Clears the console window.
     * Hint: The cursor is moved in the process.
     *
     * @author sudo200
     * @see JConsole#gotoxy(int xpos, int ypos)
     */
    public static native void clrscr();

    /**
     * Sets which type of cursor to use.
     * Hint: Use constants
     *
     * @param type Value specifying the cursor size.
     * @author sudo200
     * @see JConsole
     */
    public static native void setCursorType(int type);

    /**
     * Waits specified amount of milliseconds
     *
     * @param msec Milliseconds to wait.
     * @author sudo200
     */
    public static native void delay(int msec);

    /**
     * Disables console
     *
     * @author sudo200
     * @see JConsole#initConsole()
     */
    public static native void closeConsole();
}
