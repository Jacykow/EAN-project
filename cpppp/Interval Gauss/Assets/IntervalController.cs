using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Diagnostics;
using TMPro;
using UnityEngine.UI;
using System;
using UnityEngine.SceneManagement;

public class IntervalController : MonoBehaviour
{
    public TMP_InputField sizeInputField;
    public Transform content;
    public GameObject rowPrefab;
    public GameObject fieldPrefab;
    public Button calculateButton;

    private TMP_InputField[,] fields;

    public void ReInit()
    {
        Fill(5);
        string[,] defaultInput = new string[5, 6]
        {
            { "3.9859265",
            "-374.8678824",
            "-8.5662110918",
            "4.8650891",
            "0.99864123",
            "1" },
            { "42.7856242",
            "-4.5346826",
            "3.86425767",
            "-0.7643424",
            "6.754368",
            "2" },
            { "0.54576547138",
            "46.586424689",
            "-0.632539975",
            "4.234342458",
            "75.535008858",
            "0" },
            { "0.583563489427",
            "0.9583924",
            "-9.9543726",
            "0.83546556",
            "-857.834678",
            "-1" },
            { "0.34809870124",
            "-7.7769750323",
            "97.64870949",
            "8.56801507",
            "80",
            "-1" }
        };
        for(int y = 0; y < 5; y++)
        {
            for(int x = 0; x < 6; x++)
            {
                fields[y, x].text = defaultInput[y, x];
            }
        }
    }

    private void Start()
    {
        sizeInputField.onEndEdit.AddListener(text =>
        {
            Fill(int.Parse(text));
        });

        calculateButton.onClick.AddListener(() =>
        {
            try
            {
                FillAnswer(Calculate());
            }
            catch(Exception e)
            {
                sizeInputField.text = e.Message;
            }
        });
    }

    private void FillAnswer(Answer[] answers)
    {
        var lefts = Instantiate(rowPrefab, content).transform;
        var middles = Instantiate(rowPrefab, content).transform;
        var rights = Instantiate(rowPrefab, content).transform;
        for(int x = 0; x < answers.Length; x++)
        {
            var controller = Instantiate(fieldPrefab, lefts).GetComponent<TMP_InputField>();
            controller.text = answers[x].left;
            var c = controller.colors;
            c.normalColor = Color.blue;
            controller.colors = c;

            controller = Instantiate(fieldPrefab, middles).GetComponent<TMP_InputField>();
            controller.text = answers[x].middle;
            c = controller.colors;
            c.normalColor = Color.green;
            controller.colors = c;

            controller = Instantiate(fieldPrefab, rights).GetComponent<TMP_InputField>();
            controller.text = answers[x].right;
            c = controller.colors;
            c.normalColor = Color.blue;
            controller.colors = c;
        }
    }

    private void Fill(int size)
    {
        foreach(var child in content.GetComponentsInChildren<Transform>())
        {
            if(child != content)
            {
                Destroy(child.gameObject);
            }
        }

        fields = new TMP_InputField[size, size + 1];

        for (int y = -1; y < size; y++)
        {
            var row = Instantiate(rowPrefab, content).transform;
            for(int x = 0; x < size + 1; x++)
            {
                if (y == -1)
                {
                    var controller = Instantiate(fieldPrefab, row).GetComponent<TMP_InputField>();
                    controller.text = (x == size) ? "Free Variable" : ("Variable " + (x + 1));
                    controller.enabled = false;
                }
                else
                {
                    fields[y,x] = Instantiate(fieldPrefab, row).GetComponent<TMP_InputField>();
                }
            }
        }
    }

    private Answer[] Calculate()
    {
        int size = fields.GetLength(0);
        var answers = new Answer[size];
        
        Process p = new Process();
        p.StartInfo.WorkingDirectory = Application.streamingAssetsPath;
        p.StartInfo.FileName = p.StartInfo.WorkingDirectory + "/intervalArithmetics.exe";
        p.StartInfo.UseShellExecute = false;
        p.StartInfo.RedirectStandardInput = true;
        p.StartInfo.RedirectStandardOutput = true;
        
        p.Start();
        p.StandardInput.WriteLine(size);
        for(int y = 0; y < size; y++)
        {
            for(int x = 0; x < fields.GetLength(1); x++)
            {
                p.StandardInput.WriteLine(fields[y,x].text);
            }
        }
        p.StandardInput.Close();

        for (int x = 0; x < size; x++)
        {
            answers[x].middle = p.StandardOutput.ReadLine();
            if (x == 0)
            {
                if (answers[x].middle.Contains("No answer"))
                {
                    throw new Exception("No answer");
                }
            }
            answers[x].left = p.StandardOutput.ReadLine();
            answers[x].right = p.StandardOutput.ReadLine();
        }
        p.Close();

        return answers;
    }
}
