package com.example.gophernavigate.ui.gallery;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class GalleryViewModel extends ViewModel {

    private MutableLiveData<String> mText;

    public GalleryViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("GopherNavigator is an app designed to help " +
                "those who need to get around the University of Minnesota campus.\n" +
                "Use the search bar to look up a location on the campus and get " +
                "images that direct you to the proper place. Please be sure to follow " +
                "the images and directions carefully. Once you enter your destination, " +
                "an optimal route with two options will pop up. There is an indoor option " +
                "for navigation which maximizes indoor time on route to your destination. " +
                "The indoor option may use the GopherWay tunnels underneath the campus to " +
                "help reduce the time outdoors. The outdoor option functions similarly to " +
                "normal navigation.\n" +
                "\n" +
                "You can click on the other menu options to get to the base “Home” page " +
                "or scheduling menu. You can manually add classes or other events to your " +
                "schedule inside the schedule maker. You can also automatically transfer " +
                "your schedule from Schedule Builder by using the “Import Schedule” feature.\n");
    }

    public LiveData<String> getText() {
        return mText;
    }
}