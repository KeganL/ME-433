package com.example.admin.tcapp;


// libraries
        import android.app.Activity;
        import android.graphics.Bitmap;
        import android.graphics.Canvas;
        import android.graphics.Paint;
        import android.graphics.SurfaceTexture;
        import android.hardware.Camera;
        import android.os.Bundle;
        import android.view.SurfaceHolder;
        import android.view.SurfaceView;
        import android.view.TextureView;
        import android.view.WindowManager;
        import android.widget.SeekBar;
        import android.widget.SeekBar.OnSeekBarChangeListener;
        import android.widget.TextView;
        import java.io.IOException;
        import static android.graphics.Color.blue;
        import static android.graphics.Color.green;
        import static android.graphics.Color.red;
        import static android.graphics.Color.rgb;

public class MainActivity extends Activity implements TextureView.SurfaceTextureListener {
    private Camera mCamera;
    private TextureView mTextureView;
    private SurfaceView mSurfaceView;
    private SurfaceHolder mSurfaceHolder;
    private Bitmap bmp = Bitmap.createBitmap(640,480,Bitmap.Config.ARGB_8888);
    private Canvas canvas = new Canvas(bmp);
    private Paint paint1 = new Paint();
    private TextView mTextView;
    private SeekBar Tred;
    private SeekBar Tgreen;


    static long prevtime = 0; // for FPS calculation

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); // keeps the screen from turning off

        mSurfaceView = (SurfaceView) findViewById(R.id.surfaceview);
        mSurfaceHolder = mSurfaceView.getHolder();

        mTextureView = (TextureView) findViewById(R.id.textureview);
        mTextureView.setSurfaceTextureListener(this);

        mTextView = (TextView) findViewById(R.id.cameraStatus);

        paint1.setColor(0xffff0000); // red
        paint1.setTextSize(24);

        Tred = (SeekBar) findViewById(R.id.seekRed);
        Tgreen = (SeekBar) findViewById(R.id.seekGreen);
    }

    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        mCamera = Camera.open();
        Camera.Parameters parameters = mCamera.getParameters();
        parameters.setPreviewSize(640, 480);
        parameters.setAutoWhiteBalanceLock(true);
        parameters.setColorEffect(Camera.Parameters.EFFECT_NONE); // black and white
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_INFINITY); // no autofocusing
        mCamera.setParameters(parameters);
        mCamera.setDisplayOrientation(90); // rotate to portrait mode


        try {
            mCamera.setPreviewTexture(surface);
            mCamera.startPreview();
        } catch (IOException ioe) {
            // Something bad happened
        }
    }

    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        // Ignored, Camera does all the work for us
    }

    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        mCamera.stopPreview();
        mCamera.release();
        return true;
    }

    // the important function
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        // Invoked every time there's a new Camera preview frame
        mTextureView.getBitmap(bmp);

        final Canvas c = mSurfaceHolder.lockCanvas();
        if (c != null) {
            int RedT = Tred.getProgress();
            int GreenT = Tgreen.getProgress();

            int[] pixels1 = new int[bmp.getWidth()];
            int[] pixels2 = new int[bmp.getWidth()];

            int startY = 100; // which row in the bitmap to analyse to read
            // only look at one row in the image

            int botY = 400;

            bmp.getPixels(pixels1, 0, bmp.getWidth(), 0, startY, bmp.getWidth(), 1); // (array name, offset inside array, stride (size of row), start x, start y, num pixels to read per row, num rows to read)
            bmp.getPixels(pixels2, 0, bmp.getWidth(), 0, botY, bmp.getWidth(), 1);
            // pixels[] is the RGBA data (in black an white).
            // instead of doing center of mass on it, decide if each pixel is dark enough to consider black or white
            // then do a center of mass on the thresholded array
            int[] thresholdedPixels1 = new int[bmp.getWidth()];
            int[] thresholdedColors1 = new int[bmp.getWidth()];
            int[] thresholdedPixels2 = new int[bmp.getWidth()];
            int[] thresholdedColors2 = new int[bmp.getWidth()];
            int wbTotal = 0; // total mass
            int wbCOM = 0; // total (mass time position)
            int botTotal = 0;
            int botCOM = 0;
            int angle = 0;
            int topcompres = 1;
            //top loop
            for (int i = 0; i < bmp.getWidth(); i++) {
                // sum the red, green and blue, subtract from 255 to get the darkness of the pixel.
                // if it is greater than some value (600 here), consider it black
                // play with the 600 value if you are having issues reliably seeing the line
                if ((red(pixels1[i]) > RedT*2.55)&&((255-(green(pixels1[i])-red(pixels1[i])) > 6*GreenT))) {
                    thresholdedPixels1[i] = 255*3;
                    thresholdedColors1[i] = rgb(255, 0, 0);
                }
                else {
                    thresholdedPixels1[i] = 0;

                }

                wbTotal = wbTotal + thresholdedPixels1[i];
                wbCOM = wbCOM + thresholdedPixels1[i]*i;

            }
            //bottom loop
            for (int i = 0; i < bmp.getWidth(); i++) {
                // sum the red, green and blue, subtract from 255 to get the darkness of the pixel.
                // if it is greater than some value (600 here), consider it black
                // play with the 600 value if you are having issues reliably seeing the line
                if ((red(pixels2[i]) > RedT*2.55)&&((255-(green(pixels2[i])-red(pixels2[i])) > 6*GreenT))) {
                    thresholdedPixels2[i] = 255*3;
                    thresholdedColors2[i] = rgb(255, 0, 0);
                }
                else {
                    thresholdedPixels2[i] = 0;

                }

                botTotal = botTotal + thresholdedPixels2[i];
                botCOM = botCOM + thresholdedPixels2[i]*i;

            }
            int COM1;

            int COM2;

            if (wbTotal<=0) {
                COM1 = bmp.getWidth()/2;
                topcompres = 0;
            }
            else {
                COM1 = wbCOM/wbTotal;
                topcompres = 1;
            }

            if (botTotal<=0) {
                COM2 = bmp.getWidth()/2;
            }
            else {
                COM2 = botCOM/botTotal;
                if (topcompres >= 1){
                    angle = (COM1-COM2);
                }

            }


            // draw a circle where you think the COM is
            canvas.drawCircle(COM1, startY, 5, paint1);
            canvas.drawCircle(COM2, botY, 5, paint1);
            bmp.setPixels(thresholdedColors1, 0, bmp.getWidth(), 0, startY, bmp.getWidth(), 1);
            bmp.setPixels(thresholdedColors2, 0, bmp.getWidth(), 0, botY, bmp.getWidth(), 1);


            // also write the value as text
            canvas.drawText("COM = " + COM1, 10, 200, paint1);
            canvas.drawText("COM2 = " + COM2, 10, 220, paint1);
            canvas.drawText("THRESHR = " + RedT, 10, 300, paint1);
            canvas.drawText("THRESHG = " + GreenT, 10, 320, paint1);
            canvas.drawText("ANGLE = " + angle, 10, 340, paint1);
            c.drawBitmap(bmp, 0, 0, null);
            mSurfaceHolder.unlockCanvasAndPost(c);

            // calculate the FPS to see how fast the code is running
            long nowtime = System.currentTimeMillis();
            long diff = nowtime - prevtime;
            mTextView.setText("FPS " + 1000/diff);
            prevtime = nowtime;
        }
    }
}

