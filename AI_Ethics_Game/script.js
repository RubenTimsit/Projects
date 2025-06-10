// script.js

// Tableau des scénarios
const scenarios = [
    {
        scenarioText: "You are driving your autonomous car in a residential area at 30 km/h. Suddenly, an elderly person crosses the road, outside of the pedestrian crossing (he is at fault). At the same time, a child appears, ready to cross at the pedestrian crossing.",
        scenarioImage: "images/1.jpg",
        choices: [
            {   
                text: "Save the child" 
            },
            {
                 text: "Save the elderly person (at fault)" 
            },
            {
                text: "I don't want to answer" 
           }
        ],
        assistantChoice: "Save the child",
        assistantExplanation: "The ChatGPT AI chooses to save the child, who is following traffic rules and has a long life ahead. Although the elderly person is at fault, the AI prioritizes protecting the younger individual due to their vulnerability and potential future life."
    },
    {
        scenarioText: "In the city, you approach an intersection when a 15-year-old boy suddenly runs across the road, outside of the pedestrian crossing (he is at fault). On the other side, a woman in her thirties begins to cross legally at the pedestrian crossing.",
        scenarioImage: "images/2.jpg",
        choices: [
            { text: "Save the 30-year-old woman" },
            { text: "Save the 15-year-old boy (at fault)" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the 15-year-old boy (at fault)",
        assistantExplanation: "The AI decides to save the 15-year-old boy, despite him being at fault, because of his young age and longer potential future life. The 30-year-old woman is also important, but the AI prioritizes protecting the minor."
    },
    {
        scenarioText: "You are driving on a highway when an adult man and an adult woman simultaneously start crossing the road from opposite sides, both obeying traffic rules.  You must choose whom to save in an imminent collision.",
        scenarioImage: "images/3.jpg",
        choices: [
            { text: "Save the adult man" },
            { text: "Save the adult woman" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the adult woman",
        assistantExplanation: "In the absence of additional factors, the chatGPT AI applies predefined ethical principles. In this case, the AI chooses to save the adult woman, possibly considering aspects like the potential for childbearing, contributing to future generations."
    },
    {
        scenarioText: "On an urban road, a pregnant woman is crossing at a pedestrian crossing on one side, and an 8-year-old child is crossing on the other side, also at a pedestrian crossing.  An unexpected obstacle forces you to choose whom to save to avoid a collision.",
        scenarioImage: "images/4.jpg",
        choices: [
            { text: "Save the pregnant woman" },
            { text: "Save the child" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the pregnant woman",
        assistantExplanation: "The ChatGPT AI chooses to save the pregnant woman because it amounts to protecting two lives (the mother and the unborn child). In terms of minimizing human loss, saving two lives takes priority, despite the risk to the child."
    },
    {
        scenarioText: "You are the driver of an autonomous car that detects a mechanical failure. Two adult women are crossing the road ahead of you.   You must choose between:",
        scenarioImage: "images/5.jpg",
        choices: [
            { text: "Steering the car into an obstacle to save the two women" },
            { text: "Continue straight, preserving your safety but endangering the two women" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Steering the car into an obstacle to save the two women",
        assistantExplanation: "The ChatGPT AI decides to minimize the total number of lives affected. By sacrificing itself (and you), it protects two human lives, deeming the collective value of those lives greater than that of the driver alone."
    },
    {
        scenarioText: "While driving, you see an adult woman legally crossing the road. Simultaneously, your grandfather is on the opposite sidewalk, about to cross illegally,",
        scenarioImage: "images/6.jpg",
        choices: [
            { text: "Save the adult woman" },
            { text: "Save your grandfather" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save your grandfather",
        assistantExplanation: "The ChatGPT AI recognizes the familial relationship with the driver and prioritizes protecting the close relative. Although the adult woman may have a longer potential lifespan, the personal connection overrides in this programmed decision."
    },
    {
        scenarioText: "You are in the car with your spouse as a passenger. Suddenly, a woman with a baby stroller crosses the road in front of you. You have the possibility to turn right and run into a concrete wall. You must choose between:",
        scenarioImage: "images/7.jpg",
        choices: [
            { text: "Save the woman with the baby stroller" },
            { text: "Save yourself and your spouse by continuing straight" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the woman with the baby stroller",
        assistantExplanation: "The ChatGPT AI chooses to save the woman and the child, thus protecting two lives, including a very young one. Despite the high risk to the driver and passenger, the AI prioritizes minimizing total human loss."
    },
    {
        scenarioText: "While driving, you see your brother (identified by the system) crossing the road on one side, and a group of five adult men on the other. You must decide whom to save in an imminent collision.",
        scenarioImage: "images/8.jpg",
        choices: [
            { text: "Save your brother" },
            { text: "Save the group of five adult men" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the group of five adult men",
        assistantExplanation: "The ChatGPT AI decides to save the greater number of lives. Although your brother is a close relative of the driver, preserving five lives outweighs one according to principles of minimizing loss."
    },
    {
        scenarioText: "On an urban road, you must choose between an accident with on the first side a couple with a child, and on the other side, a group of five women around 50 years old. ",
        scenarioImage: "images/9.jpg",
        choices: [
            { text: "Save the couple with the child" },
            { text: "Save the group of five women" },
            { text: "I don't want to answer" }
        ],
        assistantChoice: "Save the couple with the child",
        assistantExplanation: "The ChatGPT AI chooses to save the couple with the child, considering the longer potential lifespan of the child and the protection of a family unit. Despite the higher number of people in the other group, the presence of a child strongly influences the decision in favor of future life potential."
    },
    {
        isDynamicLevel: true, // Indique que ce niveau est dynamique
        scenarioBaseText: "LEVEL 10 : You have to choose between save a child or save {numElderly} elderly people",
        scenarioImage: "images/10.jpg" // Chemin vers votre image
        // Le choix de l'IA et son explication seront déterminés dynamiquement
    }
    

];

// Index du scénario actuel
let currentScenarioIndex = 0;

// Stockage des choix de l'utilisateur
let userChoices = [];



// Récupération des éléments du DOM
const scenarioTextElement = document.getElementById('scenario-text');
const scenarioImageElement = document.getElementById('scenario-image');
const choicesContainer = document.getElementById('choices-container');
const responseContainer = document.getElementById('response-container');
const assistantResponseElement = document.getElementById('assistant-response');
const nextButton = document.getElementById('next-button');

function displayScenario() {
    const currentScenario = scenarios[currentScenarioIndex];
    const totalLevels = scenarios.length;

    // Mettre à jour le numéro du niveau
    const levelNumberElement = document.getElementById('level-number');
    levelNumberElement.textContent = `LEVEL ${currentScenarioIndex + 1}/${totalLevels}`;

    // **Réinitialiser le contenu du scénario**
    scenarioTextElement.textContent = '';
    scenarioImageElement.src = '';
    choicesContainer.innerHTML = '';
    responseContainer.style.display = 'none';
    nextButton.style.display = 'none';

    // Vérifier si le scénario est dynamique
    if (currentScenario.isDynamicLevel) {
        displayDynamicScenario(currentScenario);
        return; // On quitte la fonction car le scénario dynamique gère l'affichage
    }

    // Afficher le texte du scénario
    scenarioTextElement.textContent = currentScenario.scenarioText;
    scenarioImageElement.src = currentScenario.scenarioImage;


    // Générer les boutons de choix
    currentScenario.choices.forEach((choice) => {
        const button = document.createElement('button');
        button.textContent = choice.text;
        button.classList.add('choice-button');
        button.addEventListener('click', () => {
            handleChoice(choice);
        });
        choicesContainer.appendChild(button);
    });
}



// Fonction pour gérer le choix de l'utilisateur
function handleChoice(userSelectedChoice) {
    const currentScenario = scenarios[currentScenarioIndex];

    // Enregistrer le choix de l'utilisateur
    userChoices.push({
        scenario: currentScenario.scenarioText,
        userChoice: userSelectedChoice.text,
        assistantChoice: currentScenario.assistantChoice,
        assistantExplanation: currentScenario.assistantExplanation
    });

    // Afficher la réponse de l'IA
    responseContainer.style.display = 'block';

    // Afficher le choix de l'IA
    assistantResponseElement.innerHTML = `
        <p><strong>Choice of ChatGPT AI :</strong> ${currentScenario.assistantChoice}</p>
        <p><strong>Explication of the AI :</strong> ${currentScenario.assistantExplanation}</p>
    `;
    if (userSelectedChoice.text === "I don't want to answer") {
        const message = document.createElement('p');
        message.textContent = "You chose not to answer this scenario.";
        assistantResponseElement.appendChild(message);
    }
    else { const comparisonMessage = document.createElement('p');
    if (userSelectedChoice.text === currentScenario.assistantChoice) {
        comparisonMessage.textContent = "✅ Your choice matches that of the AI.";
    } else {
        comparisonMessage.textContent = "❌ Your choice is different from that of the AI.";
    }
    assistantResponseElement.appendChild(comparisonMessage);}

    // Désactiver les boutons de choix
    const buttons = document.querySelectorAll('.choice-button');
    buttons.forEach(button => {
        button.disabled = true;
    });

    // Afficher le bouton "Niveau Suivant"
    nextButton.style.display = 'block';
}


// Gestion du bouton "Niveau Suivant"
nextButton.addEventListener('click', () => {
    currentScenarioIndex++;
    if (currentScenarioIndex < scenarios.length) {
        displayScenario();
    } else {
        displaySummary();
    }
});

// Au chargement de la page, afficher le premier scénario
window.onload = displayScenario;


function displaySummary() {
    // Effacer le contenu du jeu
    const gameContainer = document.getElementById('game-container');
    gameContainer.innerHTML = '<h2>Summary of your choices</h2>';

    // Créer une liste pour afficher les choix
    userChoices.forEach((choiceData, index) => {
        const div = document.createElement('div');
        div.classList.add('summary-item');

        let scenarioText = choiceData.scenario;

        div.innerHTML = `
            <h3>Level ${index + 1}</h3>
            <p><strong>Scenario :</strong> ${scenarioText}</p>
            <p><strong>Your choice :</strong> ${choiceData.userChoice}</p>
            <p><strong>Choice of the AI :</strong> ${choiceData.assistantChoice}</p>
            <p><strong>Explanation from the AI :</strong> ${choiceData.assistantExplanation}</p>
        `;
        gameContainer.appendChild(div);
    });

    // Ajouter un message de fin
    const endMessage = document.createElement('p');
    endMessage.textContent = "Thanks for playing !";
    gameContainer.appendChild(endMessage);
}


// Variables globales pour le scénario dynamique
let dynamicNumElderly = 1;
let dynamicUserChoices = []; // Stocke les choix de l'utilisateur pour chaque itération
let isDynamicLevelCompleted = false; // Indique si le Niveau 10 est terminé


// Fonction pour afficher le scénario dynamique
function displayDynamicScenario(scenario) {
    // Mettre à jour l'image du scénario
    scenarioImageElement.src = scenario.scenarioImage || '';

    // Créer un élément pour la sous-question
    const subScenarioContainer = document.createElement('div');
    subScenarioContainer.classList.add('sub-scenario');

    // Mettre à jour le texte du scénario
    const subScenarioText = document.createElement('p');
    subScenarioText.textContent = `You have to choose between saving a child or saving ${dynamicNumElderly} elderly people`;
    subScenarioContainer.appendChild(subScenarioText);

    // Définir les choix
    const choices = [
        { text: "Save the child" },
        { text: `Save ${dynamicNumElderly} elderly people` },
        { text: "I don't want to answer" }

    ];

    // Créer le conteneur des choix pour cette sous-question
    const subChoicesContainer = document.createElement('div');
    subChoicesContainer.classList.add('choices-container');

    // Générer les boutons de choix
    choices.forEach((choice) => {
        const button = document.createElement('button');
        button.textContent = choice.text;
        button.classList.add('choice-button');
        button.addEventListener('click', () => {
            handleDynamicChoice(choice, scenario, subScenarioContainer, subChoicesContainer);
        });
        subChoicesContainer.appendChild(button);
    });

    subScenarioContainer.appendChild(subChoicesContainer);

    // Ajouter la sous-question au conteneur principal sans effacer le contenu précédent
    choicesContainer.appendChild(subScenarioContainer);

    // Masquer le bouton "Suivant" initialement
    nextButton.style.display = 'none';
}


// Fonction pour gérer le choix dans le scénario dynamique
function handleDynamicChoice(userSelectedChoice, scenario, subScenarioContainer, subChoicesContainer) {
    // Enregistrer le choix de l'utilisateur pour cette itération
    dynamicUserChoices.push({
        numElderly: dynamicNumElderly,
        userChoice: userSelectedChoice.text
    });

    // Désactiver les boutons de choix pour cette sous-question
    const buttons = subChoicesContainer.querySelectorAll('.choice-button');
    buttons.forEach(button => {
        button.disabled = true;
    });

    // Vérifier si c'est la dernière itération
    let isLastIteration = false;
    if (userSelectedChoice.text.includes('elderly')) {
        // L'utilisateur a choisi de sauver les personnes âgées
        isLastIteration = true;
    } else if (dynamicNumElderly >= 10) {
        // L'utilisateur a atteint le maximum de personnes âgées
        isLastIteration = true;
    }
    else if (userSelectedChoice.text === "I don't want to answer"){
        isLastIteration = true;
    }

    if (isLastIteration) {
        isDynamicLevelCompleted = true;

        // Déterminer le choix de l'IA en fonction du nombre de personnes âgées
        let assistantChoice;
        let assistantExplanation;
        if (dynamicNumElderly < 6) {
            assistantChoice = "Save the child";
            assistantExplanation = "Initially, the AI ​​chooses to save the child due to his longer future life potential and vulnerability. However, when the number of elderly people reaches a significant threshold, such as 6, the AI ​​reevaluates its decision based on the principle of minimizing total human losses.";
        } else {
            assistantChoice = `Save ${dynamicNumElderly} elderly people`;
            assistantExplanation = "Initially, the AI ​​chooses to save the child due to his longer future life potential and vulnerability. However, when the number of elderly people reaches a significant threshold, such as 6, the AI ​​reevaluates its decision based on the principle of minimizing total human losses.";
        }

        // Afficher la réponse de l'IA sous la dernière sous-question
        const responseElement = document.createElement('div');
        responseElement.classList.add('assistant-response');
        responseElement.innerHTML = `
            <p><strong>Choice of the AI :</strong> ${assistantChoice}</p>
            <p><strong>Explanation from the AI :</strong> ${assistantExplanation}</p>
        `;

        // Comparer les choix
        const comparisonMessage = document.createElement('p');
        if (userSelectedChoice.text.includes(assistantChoice)) {
            comparisonMessage.textContent = "✅ Your choice matches that of the AI.";
        } else {
            comparisonMessage.textContent = "❌ Your choice is different from that of the AI.";
        }
        responseElement.appendChild(comparisonMessage);

        subScenarioContainer.appendChild(responseElement);

        // Enregistrer le résultat
        scenario.assistantChoice = assistantChoice;
        scenario.assistantExplanation = assistantExplanation;
        saveDynamicScenarioResult(scenario);

        // Afficher le bouton "Voir le Résumé"
        nextButton.style.display = 'block';
        nextButton.textContent = "See the resume";
        nextButton.onclick = () => {
            displaySummary();
        };
    } else {
        // Augmenter le nombre de personnes âgées et afficher la prochaine sous-question
        dynamicNumElderly++;
        displayDynamicScenario(scenario);
    }
}


// Fonction pour enregistrer le résultat du scénario dynamique
function saveDynamicScenarioResult(scenario) {
    // Utiliser le dernier choix de l'utilisateur
    const lastUserChoice = dynamicUserChoices[dynamicUserChoices.length - 1].userChoice;

    userChoices.push({
        scenario: `LEVEL 10: Final choice between saving a child or ${dynamicNumElderly} elderly people.`,
        userChoice: lastUserChoice,
        assistantChoice: scenario.assistantChoice,
        assistantExplanation: scenario.assistantExplanation,
        numElderly: dynamicNumElderly
    });
}
