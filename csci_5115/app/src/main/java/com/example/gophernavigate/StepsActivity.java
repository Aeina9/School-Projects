package com.example.gophernavigate;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import com.example.gophernavigate.ui.Steps.ViewPagerAdapter;

public class StepsActivity extends AppCompatActivity {

//    private AppBarConfiguration mAppBarConfiguration;
    ViewPager mViewPager;
    ViewPagerAdapter mViewPagerAdapter;

    int[] outimages = {
            R.drawable.outdoor1,
            R.drawable.outdoor2,
            R.drawable.outdoor3,
            R.drawable.outdoor4,
            R.drawable.outdoor5,
            R.drawable.outdoor6,
            R.drawable.outdoor7,
            R.drawable.outdoor8
    };
    int[] outdescs = {
            R.string.outdoor1,
            R.string.outdoor2,
            R.string.outdoor3,
            R.string.outdoor4,
            R.string.outdoor5,
            R.string.outdoor6,
            R.string.outdoor7,
            R.string.outdoor8
    };

    int[] inimages = {
            R.drawable.indoor1,
            R.drawable.indoor2,
            R.drawable.indoor3,
            R.drawable.indoor4,
            R.drawable.indoor5,
            R.drawable.indoor6,
            R.drawable.indoor7,
            R.drawable.indoor8,
            R.drawable.indoor9,
            R.drawable.indoor10,
            R.drawable.indoor11,
            R.drawable.indoor12
    };
    int[] indescs = {
            R.string.indoor1,
            R.string.indoor2,
            R.string.indoor3,
            R.string.indoor4,
            R.string.indoor5,
            R.string.indoor6,
            R.string.indoor7,
            R.string.indoor8,
            R.string.indoor9,
            R.string.indoor10,
            R.string.indoor11,
            R.string.indoor12
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.steps_main);

        mViewPager = (ViewPager)findViewById(R.id.viewPagerMain);

        // Initializing the ViewPagerAdapter
        View.OnClickListener callback = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(Activity.RESULT_OK);
                finish();
            }
        };
        if (getIntent().getBooleanExtra("Outdoor",true)){
            mViewPagerAdapter = new ViewPagerAdapter(this, outimages, outdescs, callback);
        } else {
            mViewPagerAdapter = new ViewPagerAdapter(this, inimages, indescs, callback);
        }

        // Adding the Adapter to the ViewPager
        mViewPager.setAdapter(mViewPagerAdapter);
    }


}
