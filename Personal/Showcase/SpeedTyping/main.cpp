#include <iostream>
#include <vector>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <chrono>

std::string clearConsole = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ";

int consoleWidth = 0;

HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

DWORD dwBytesWritten = 0;

void print(std::string text)
{
    WriteConsoleOutputCharacter(hConsole, text.c_str(), text.size(), {0, 0}, &dwBytesWritten);
}

void addToText(std::string *text, std::string *addText, int newLine)
{
    if (newLine == 0)
        (*text) += (*addText);
    else if (newLine == 1)
    {
        int a = consoleWidth - (*text).size() % consoleWidth;
        for (int i = 0; i < a; i++)
            (*text) += ' ';
        (*text) += (*addText);
    }
    else if (newLine == 2)
    {
        int a = consoleWidth - (*text).size() % consoleWidth;
        for (int i = 0; i < a + (consoleWidth / 2) - (((*addText).size()) / 2) - 2; i++)
            (*text) += ' ';
        (*text) += (*addText);
    }
}

int main(int argc, char const *argv[])
{

    std::cout << "Please input your cmd line width (width value in properties)" << std::endl;

    std::cin >> consoleWidth;

    std::string texts[36] = {
        {"The University of Sydney offers both undergraduate and postgraduate programmes in the History and Philosophy of Science, run by the Unit for the History and Philosophy of Science, within the Science Faculty. Undergraduate coursework can be completed as part of either a Bachelor of Science or a Bachelor of Arts Degree."},
        {"Hack-for-hire operations are services that provide clients with illicit access to information by infiltrating digital systems or networks, typically for a fee. This form of hacking on demand has seen a surge in popularity over recent years, with the trend being attributed to advancements in technology, growing digital connectivity, and increasing demand for corporate espionage and personal data breaches."},
        {"Once a statement is cast into mathematical form it may be manipulated in accordance with these rules and every configuration of the symbols will represent facts in harmony with and dependent on those contained in the original statement. Now this comes very close to what we conceive the action of the brain structures to be in performing intellectual acts with the symbols of ordinary language."},
        {"Often simply referred to as \"The Plague\", the Black Death had both immediate and long-term effects on human population across the world as one of the most devastating pandemics in human history, including a series of biological, social, economic, political and religious upheavals that had profound effects on the course of world history, especially European history."},
        {"Chinese-speaking Muslims in the northwest were called the Dungans, transcribed as Tungan, Dungan, or Donggan. They were also called hanhui in Qing documents. The oasis peoples of Xinjiang referred to themselves as musulman to distinguish themselves from the Dungans."},
        {"The mineral resource-rich countries of Central Asia and Mongolia offer a unique set of landlocked cases to explore in more depth, as these are nations where economic growth has grown exceptionally in recent years. In Central Asia, oil and coal deposits have influenced development: Kazakhstan's GDI per capita in purchasing power parity was five times greater than Kyrgyzstan's in 2009."},
        {"The Republic of Armenia is a landlocked country having geographic disadvantages and faces limitations on foreign policy options. It needs to transport its goods via coastal neighbors to access ports to participate in international trade, to which Azerbaijan and Turkey are hostile and deny its access. Therefore, Armenia mainly depends on the Georgian ports of Batumi and Poti and the Georgian train system to participate in international trade."},
        {"The Hjulstrom curve, named after Filip Hjulstrom , is a graph used by hydrologists and geologists to determine whether a river will erode, transport, or deposit sediment. It was originally published in his doctoral thesis \"Studies of the morphological activity of rivers as illustrated by the River Fyris.\""},
        {"Back to nature or return to nature is a philosophy or style of living which emphasises closeness to nature, rather than artifice and civilisation. In this, the rustic customs and pastoralism of country life are preferred to urban fashion and sophistication."},
        {"Evolution is any process of growth or development that entails change. The word stems from the Latin evolutio meaning \" unfolding \" and before the late 19th century was confined to referring to goal-directed, pre-programmed processes such as embryological development. A pre-programmed task, as in a military maneuver, using this definition, may be termed an evolution"},
        {"In Crabtree-negative species, respiration related genes are highly expressed in the presence of oxygen. However, when S. cerevisiae is grown on glucose in aerobic conditions, respiration-related gene expression is repressed. Mitochondrial ribosomal proteins expression is only induced under environmental stress conditions, specifically low glucose availability."},
        {"Russia currently implements a variety of anti-alcoholism measures, banning spirits and beer trade at night, raising taxes, banning the advertising of alcohol. According to medical officials, these policies have resulted in a considerable fall of alcohol consumption volumes, to 13.5 litres by 2013, with wine and beer overtaking spirits as the main source of beverage alcohol."},
        {"Securely attached people generally have positive views about themselves and about others. They tend to agree with statements \\It is relatively easy for me to become emotionally close to others. I am comfortable depending on others and having others depend on me. I don't worry about being alone or others not accepting me.\""},
        {"Health Disparities Centers are institutions in the United States that cover a broad range of needs and focus areas to decrease currently disproportionate illness and disease rates that lead to health disparities. They also promote the engagement, empowerment and recruitment of underrepresented populations in health professions."},
        {"It is a common misconception that Health Disparities Centers are tailored primarily for minorities, but in actuality their mission extends to a wide range of groups. These include age, gender, ethnicity, geographical location, language barriers, or any other differences related to socioeconomic status or environmental factors."},
        {"Health systems are organizations established to meet the health needs of targeted populations. According to the World Health Organization, a well-functioning healthcare system requires a financing mechanism, a well-trained and adequately paid workforce, reliable information on which to base decisions and policies, and well-maintained health facilities to deliver quality medicines and technologies."},
        {"Primary care involves the widest scope of health care, including all ages of patients, patients of all socioeconomic and geographic origins, patients seeking to maintain optimal health, and patients with all types of acute and chronic physical, mental and social health issues, including multiple chronic diseases. Consequently, a primary care practitioner must possess a wide breadth of knowledge in many areas."},
        {"In the Middle Ages, there were two prevailing approaches to those with disabilities. Some priests and scholars took the view that disability was a punishment from God for committing sins, as is often described in the Bible. Others believed that those with disabilities were more pious than non-disabled people."},
        {"The aims of the Trans-European Drug Information project are to collect, monitor and analyze the evolution of the European recreational drug market trends, and to regularly report the findings. Since 2011, the database has facilitated the centralization and comparison of information collected at the local level."},
        {"Health Disparities Centers are institutions in the United States that cover a broad range of needs and focus areas to decrease currently disproportionate illness and disease rates that lead to health disparities. They also promote the engagement, empowerment and recruitment of underrepresented populations in health professions."},
        {"As disproportionate burdens of certain diseases and health conditions among specific populations are a growing concern, so is the need for widespread education and training for both the public and health professionals alike to be able to cope with, and prevent the occurrence of growing disparities in their communities."},
        {"Environment factors contribute to health disparities. Environmental justice refers to the burden that certain groups experience due to the physical environment that encompasses there day-to-day lives. People in different geographical locations may experience health disparities due to pollutants in the food or air, stress factors caused by their physical environment, and availability of different resources."},
        {"To compound all of these issues, the burden of acculturation is an added stressor. Navigating the divide between the heritage culture and the culture of the new society is difficult, as the traditions, beliefs, and norms of these two cultures are often in direct conflict. This challenge is only compounded by the other obstacles immigrants are faced with, and has deleterious consequences for mental health."},
        {"here is a general consensus that refugees are at a particular disadvantage when it comes to successful resettlement in the host society, as the same challenges voluntary immigrants face are generally aggravated for refugees. However, some research has found evidence of a paradox, with refugees at least three times less likely to engage in substance use than non-immigrants."},
        {"Social relationships have short-term and long-term effects on health, both mental and physical. In a lifespan perspective, recent research suggests that early life experiences still have consequences on health behavior in adulthood. Indeed, either positive or negative effects of relationships tend to foster cumulative advantage or disadvantage in health."},
        {"Furthermore, social support can help us to regulate emotions above all when we are facing a stressful event. Probably one of the most famous studies on this field of investigation was conducted by Coan, Schaefer, and Davidson. In their study, they told married couples to go together in the laboratory. All couples reported a high level of marital satisfaction."},
        {"Aircraft noise is noise pollution produced by an aircraft or its components, whether on the ground while parked such as auxiliary power units, while taxiing, on run-up from propeller and jet exhaust, during takeoff, underneath and lateral to departure and arrival paths, over-flying while en route, or during landing. A moving aircraft including the jet engine or propeller causes compression and rarefaction of the air, producing motion of air molecules."},
        {"A large-scale statistical analysis of the health effects of aircraft noise was undertaken in the late 2000s by Bernhard Greiser for the Umweltbundesamt, Germany's central environmental office. The health data of over one million residents around the Cologne airport were analysed for health effects correlating with aircraft noise."},
        {"Just as there was a shift from viewing disease as a state to thinking of it as a process, the same shift happened in definitions of health. Again, the WHO played a leading role when it fostered the development of the health promotion movement in the 1980s. This brought in a new conception of health, not as a state, but in dynamic terms of resiliency, in other words, as \"a resource for living\"."},
        {"Attachment and health interact on multiple levels. Attachment is a biologically based system tied to our response to distress and attachment styles appear to confer differences in stress physiology. Illness and pain themselves act as an \"activating signal\" for attachment systems, and health care providers act as attachment figures in their role addressing illness and pain."},
        {"Health Disparities Centers are institutions in the United States that cover a broad range of needs and focus areas to decrease currently disproportionate illness and disease rates that lead to health disparities. They also promote the engagement, empowerment and recruitment of underrepresented populations in health professions."},
        {"Annual Health Fairs provided at Voorhees College for community residents allow attendees to receive health services and information. At these fairs, people can receive free information about nutrition, physical activities and general health-care. They can also receive blood pressure and blood sugar checks and learn about maintaining their body mass index."},
        {"The administration component of numerous Health Disparities Centers is responsible for the oversight and management of all center initiatives and programs and ensures the fiscal responsibility of the institution. It is also common for the governing body of a health disparities center to manage grants and collaborative partnerships between the center and various university, hospital or community entities."},
        {"This early virtual event marketplace is now moving towards 3D persistent environments, where enterprises combine e-commerce, social media as core operating systems, and is evolving into virtual environments for branding, customer acquisition, and service centers. A persistent environment enables users, visitors and administrators to re-visit a part or parts of the event or session."},
        {"The first major elaboration of a technological determinist view of socioeconomic development came from the German philosopher and economist Karl Marx, who argued that changes in technology, and specifically productive technology, are the primary influence on human social relations and organizational structure, and that social relations and cultural practices ultimately revolve around the technological and economic base of a given society."},
        {"Test sentence"},
    };

    SetConsoleActiveScreenBuffer(hConsole);

    srand(time(NULL));

    bool word = true;

    while (word)
    {
        for (int i = 0; i < 5; i++)
        {
            std::string starting = "";
            addToText(&starting, new std::string("Starting in: " + std::to_string(5 - i)), 2);
            print(starting), sleep(1), print(clearConsole);
        }

        word = true;

        int number = rand() % 35;

        std::string tmp = texts[number];

        int progress = 0;

        int mistakes = 0;

        auto time_start = std::chrono::system_clock::now();

        while (true)
        {

            std::string printed;
            addToText(&printed, &texts[number], 0);

            int t = 0;

            addToText(&printed, new std::string(" "), 1);
            addToText(&printed, new std::string("Waiting for - "), 1);

            printed += texts[number][progress];

            print(printed);

            char ch = _getch();

            if (ch == texts[number][progress])
            {
                texts[number][progress] = ' ';
                progress++;
                if (progress >= texts[number].size())
                {
                    std::string results;
                    print(clearConsole);
                    addToText(&results, new std::string("Congratulations. Your stats: "), 2);

                    addToText(&results, new std::string("Written text length: "), 2);
                    results += std::to_string(tmp.size());

                    addToText(&results, new std::string("Total keys pressed: "), 2);
                    results += std::to_string(mistakes + tmp.size());

                    addToText(&results, new std::string("Typing speed: "), 2);
                    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - time_start;
                    double tme = std::chrono::duration<double>(elapsed_seconds).count();
                    results += std::to_string((int)(((texts[number].size() / 5) / tme) * 60)) + " WPM";

                    addToText(&results, new std::string("Misinputs: "), 2);
                    results += std::to_string(mistakes);

                    addToText(&results, new std::string("Accuracy: "), 2);
                    results += std::to_string((int)(((float)tmp.size() / (mistakes + tmp.size())) * 100)) + " %";

                    addToText(&results, new std::string("Press any key to continue"), 2);
                    print(results);
                    while (_getch() != 13)
                    {
                        /* code */
                    }

                    break;
                }
            }
            else if ((int)ch == 8)
                continue;
            else
                mistakes++;
        }

        print(clearConsole);
        texts[number] = tmp;
    }

    return 0;
}