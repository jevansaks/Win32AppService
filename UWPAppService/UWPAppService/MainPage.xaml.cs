using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.AppService;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace UWPAppService
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            var connection = new AppServiceConnection();

            var appservicename = "com.microsoft.universalaction";
            var providers = (await AppServiceCatalog.FindAppServiceProvidersAsync(appservicename)).ToList();

            foreach (var provider in providers)
            {
                connection.AppServiceName = appservicename;
                connection.PackageFamilyName = provider.PackageFamilyName;
            }

            var status = await connection.OpenAsync();

            if (status != AppServiceConnectionStatus.Success)
            {
                return;
            }

            //// Call the service.
            //int idx = int.Parse(textBox.Text);
            //var message = new ValueSet();
            //message.Add("Command", "Item");
            //message.Add("ID", idx);
            //AppServiceResponse response = await this.inventoryService.SendMessageAsync(message);
            //string result = "";

            //if (response.Status == AppServiceResponseStatus.Success)
            //{
            //    // Get the data  that the service sent to us.
            //    if (response.Message["Status"] as string == "OK")
            //    {
            //        result = response.Message["Result"] as string;
            //    }
            //}

            //message.Clear();
            //message.Add("Command", "Price");
            //message.Add("ID", idx);
            //response = await this.inventoryService.SendMessageAsync(message);

            //if (response.Status == AppServiceResponseStatus.Success)
            //{
            //    // Get the data that the service sent to us.
            //    if (response.Message["Status"] as string == "OK")
            //    {
            //        result += " : Price = " + response.Message["Result"] as string;
            //    }
            //}

            //textBox.Text = result;

        }
    }
}
