package com.example.gophernavigate.ui.Steps;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.PagerAdapter;

import com.example.gophernavigate.R;

import org.w3c.dom.Text;

import java.util.Objects;

public class ViewPagerAdapter extends PagerAdapter {

    // Context object 
    Context context;

    // Array of images
    int[] images;
    int[] descriptions;

    // Layout Inflater
    LayoutInflater mLayoutInflater;

    View.OnClickListener callback;


    // Viewpager Constructor 
    public ViewPagerAdapter(Context context, int[] images, int[] descriptions, View.OnClickListener callback) {
        this.context = context;
        this.images = images;
        this.descriptions = descriptions;
        this.callback = callback;
        mLayoutInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        // return the number of images
        return images.length;
    }

    @Override
    public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
        return view == ((LinearLayout) object);
    }

    @NonNull
    @Override
    public Object instantiateItem(@NonNull final ViewGroup container, final int position) {
        // inflating the item.xml 
        View itemView = mLayoutInflater.inflate(R.layout.individual_step, container, false);

//         referencing the image view from the item.xml file
        ImageView imageView = (ImageView) itemView.findViewById(R.id.imageViewMain);

//         setting the image in the imageView
        imageView.setImageResource(images[position]);


        TextView description = (TextView) itemView.findViewById(R.id.stepDescText);
        description.setText(descriptions[position]);

        TextView counter = (TextView) itemView.findViewById(R.id.stepCountText);
        counter.setText(String.format("Step %d/%d",position+1,images.length));

        Button endNav = (Button) itemView.findViewById(R.id.endnavButton);
        final ViewPagerAdapter parent = this;
        if (position+1 == images.length) {
            endNav.setAlpha(1);
            endNav.setOnClickListener(callback);
        }

//         Adding the View
        if (container != null) container.addView(itemView);

        return itemView;
    }

    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {

        container.removeView((LinearLayout) object);
    }
}