package com.example.android.jniclient;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;
import android.widget.TextView;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import com.example.android.jniapi.RoadToSystem;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView outTextView = (TextView)findViewById(R.id.outText);

        if (RoadToSystem.getInstance().linkSystemLib() != 0) {
            outTextView.setText("Access granted");
        } else {
            outTextView.setText("Access denied");
        }
    }
}
